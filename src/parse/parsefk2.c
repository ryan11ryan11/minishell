/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:04:43 by jbober            #+#    #+#             */
/*   Updated: 2024/10/22 17:13:23 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char		*ms_parsefk2_ctrl(t_data *data);
static char	*ms_checkex(t_data *data, char *str, int weakqt, int strongqt);
int			ms_get_lenterm(char *str, int l);
char		*ms_get_value(t_data *data, char *str, int l, int lenterm);
static int	ms_findexpanse(t_data *data, char *str);

/**
 * Control structure
 * Expands $*
 */
char	*ms_parsefk2_ctrl(t_data *data)
{
	char	*newstr;

	newstr = ms_checkex(data, data->currinput, 0, 42);
	if (!newstr)
		return (NULL);
	data->currinput = ms_strdup(newstr);
	free(newstr);
	if (!data->currinput)
		return (NULL);
	return (data->currinput);
}

/**
 * Checks str for $, expands them
 * Returns malloced str
 * Given str gets freed is freed (in removeterm/strjoin)
 */
static char	*ms_checkex(t_data *data, char *str, int weakqt, int strongqt)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((ms_check_qt(str[i], &weakqt, &strongqt) < 2) && (str[i] == 36)
			&& (str[i + 1] && str[i + 1] != 32 && str[i + 1] != 34))
		{
			if (str[i + 1] && str[i + 1] == 36)
			{
				i++;
				break ;
			}
			str = ms_replace_term(data, str, i);
			if (!str)
				return (NULL);
			i--;
		}
		if (i == -1 || str[i])
			i++;
	}
	return (str);
}

/**
 * Returns len of $TERM in TERM=VALUE
 * str[l] == $
 */
int	ms_get_lenterm(char *str, int l)
{
	int	i;

	i = 1;
	if (str[l + 1] == 63)
		return (2);
	while (!(ms_cinset(str[l + i], " \t\n=:;|&'\"`(){}/$?*@\0", 1)))
		i++;
	return (i);
}

/**
 * Copies TERM in $TERM to lookme
 * Checks wether it finds TERM in env[k]
 * strdups lookme to the value of env[k]
 * Returns malloced *str which is VALUE in TERM=VALUE
 * lenterm == $TERM, while lookeme is "TERM", thus we don't need the usual +1
 * 		+1 becuse we want the =, too, so we don't confuse USER= with USER_ZOO=
 *	str = str to ?, l = index to $ in $TERM, lenterm = strlen of $TERM
 */
char	*ms_get_value(t_data *data, char *str, int l, int lenterm)
{
	int		i;
	int		k;
	char	*lookme;

	i = 0;
	if (str[l + 1] && str[l + 1] == 63)
		return (ms_itoa(g_lastexit));
	lookme = malloc((lenterm + 1) * sizeof(char));
	if (!lookme)
		return (NULL);
	while ((str[i + l + 1]) && (i + 1 < lenterm))
	{
		lookme[i] = str[i + l + 1];
		i++;
	}
	lookme[i] = 61;
	lookme[i + 1] = '\0';
	k = ms_findexpanse(data, lookme);
	free(lookme);
	if (k == -1)
		return (ms_strdup("Hy7J$Lm3Pq1Rx4Vz8!@#^&*()_+{}|:<>?`~"));
	lookme = ms_strdup(data->env[k] + lenterm);
	return (lookme);
}

/**
 * Checks **env for *str
 * On Found, return k (as in env[k])
 * If not found, return -1
 */
static int	ms_findexpanse(t_data *data, char *str)
{
	int	k;

	k = 0;
	while (data->env[k])
	{
		if (!ms_strncmp(data->env[k], str, ms_strlen(str)))
			return (k);
		k++;
	}
	return (-1);
}
