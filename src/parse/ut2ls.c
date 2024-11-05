/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut2ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:46:15 by jbober            #+#    #+#             */
/*   Updated: 2024/10/22 17:14:45 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ms_strncmp(char	*set, char *str, int len);
char	*ms_strdup(char *str);
int		ms_strlen(char *str);
int		ms_checkmds(t_data *data);

/**
 * Checks wether chars *set and *str are the same
 * Returns 0 if yes, something else if no
*/
int	ms_strncmp(char	*set, char *str, int len)
{
	int	i;

	i = 0;
	if (!len)
		return (0);
	while (set[i] && str[i] && i < len)
	{
		if (set[i] != str[i])
			return ((unsigned char)set[i] - (unsigned char)str[i]);
		i++;
	}
	if (i == len)
		i--;
	return ((unsigned char)set[i] - (unsigned char)str[i]);
}

/**
 * Mallocs and returns pointer to copy of str
 * Does not free str
 * Returns NULL on failloc
 */
char	*ms_strdup(char *str)
{
	int		i;
	char	*newstr;

	i = 0;
	if (!str)
		return (NULL);
	newstr = malloc((ms_strlen(str) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

/**
 * Returns the lenght of the given str
*/
int	ms_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ms_checkmds(t_data *data)
{
	int	k;

	k = 0;
	while (data->currstr[k])
	{
		if (data->currstr[k][0] && (data->currstr[k][0] == 60
			|| data->currstr[k][0] == 62 || data->currstr[k][0] == 124))
		{
			if (!data->currstr[k + 1])
				return (0);
		}
		k++;
	}
	return (1);
}
