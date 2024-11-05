/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk2b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:19:02 by jbober            #+#    #+#             */
/*   Updated: 2024/10/22 17:07:28 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char		*ms_replace_term(t_data *data, char *str1ng, int l);
static void	ms_replace(char *bigstr, char *str1ng, char *str2ng, int l);
static char	*ms_remove_term(char *str1ng, char *freeme, int l, int lenterm);
static void	ms_trim(char *str, int *lenterm, int *l);

/**
 * Returns a str with "VALUE" instead of $TERM with $TERM=VALUE
 * 		to be clear, "VALUE" comes with quotes (that's why malloc +3)
 * If $TERM=FAKE, will return str without $TERM and without leading space
 * Frees str1ng
 * l = index to $ in $TERM
 * lenterm = len of $TERM
 */
char	*ms_replace_term(t_data *data, char *str1ng, int l)
{
	int		lenterm;
	char	*bigstr;
	char	*str2ng;

	lenterm = ms_get_lenterm(str1ng, l);
	str2ng = ms_get_value(data, str1ng, l, lenterm);
	if (!str2ng)
	{
		free(str1ng);
		return (NULL);
	}
	if (!ms_strncmp("Hy7J$Lm3Pq1Rx4Vz8!@#^&*()_+{}|:<>?`~", str2ng, 36))
		return (ms_remove_term(str1ng, str2ng, l, lenterm));
	bigstr = malloc(ms_strlen(str1ng) + ms_strlen(str2ng) - lenterm + 3);
	if (!bigstr)
	{
		free (str1ng);
		free (str2ng);
		return (NULL);
	}
	bigstr[ms_strlen(str1ng) + ms_strlen(str2ng) - lenterm + 2] = '\0';
	ms_replace(bigstr, str1ng, str2ng, l);
	free (str1ng);
	free (str2ng);
	return (bigstr);
}

/**
 * Fills bigstr with str1ng until l, str2ng, rest of str1ng
 * bigstr = malloced str to fill
 * l = index to $ in $TERM
 */
static void	ms_replace(char *bigstr, char *str1ng, char *str2ng, int l)
{
	int	i;
	int	j;
	int	lenterm;

	i = 0;
	j = 0;
	lenterm = ms_get_lenterm(str1ng, l);
	while (i < l)
	{
		bigstr[i] = str1ng[i];
		i++;
	}
	bigstr[i] = 34;
	while ((i + j) < (l + ms_strlen(str2ng)))
	{
		bigstr[1 + i + j] = str2ng[j];
		j++;
	}
	bigstr[1 + i + j] = 34;
	while ((l + lenterm) < (ms_strlen(str1ng)))
	{
		bigstr[2 + l + ms_strlen(str2ng)] = str1ng[l + lenterm];
		l++;
	}
}

/**
 * Returns a malloced *str made out of str1ng removing the $TERM with $ at l
 * For $FAKE, lenterm = 5
 * Frees str1ng and freeme
 */
static char	*ms_remove_term(char *str1ng, char *freeme, int l, int lenterm)
{
	int		i;
	char	*newstr;

	i = 0;
	ms_trim(str1ng, &lenterm, &l);
	newstr = malloc(ms_strlen(str1ng) - lenterm + 1);
	if (!newstr)
		return (NULL);
	while (i < l)
	{
		newstr[i] = str1ng[i];
		i++;
	}
	while (i < (ms_strlen(str1ng) - lenterm))
	{
		newstr[i] = str1ng[i + lenterm];
		i++;
	}
	newstr[i] = '\0';
	free(str1ng);
	free(freeme);
	return (newstr);
}

/**
 * If $FAKE is followed by a space, trim lenterm && l to remove it
 */
static void	ms_trim(char *str, int *lenterm, int *l)
{
	if (*l == 0 && str[*lenterm] && str[*lenterm] == 32)
		(*lenterm)++;
	if (*l != 0 && str[*l - 1] && str[*l - 1] == 32)
	{
		(*l)--;
		(*lenterm)++;
	}
}
