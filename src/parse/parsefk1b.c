/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk1b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:22:02 by jbober            #+#    #+#             */
/*   Updated: 2024/10/17 16:15:21 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char		*ms_add_32(char *str, int weakqt, int strongqt);
static void	ms_add_32_ext(char *str, char *newstr, int *i, int *j);
static int	ms_size_32(char *str, int weakqt, int strongqt);
static int	ms_check_delim(char *str, int i);
static int	ms_check_delimb(char *str, int i);

/**
 * Returns copy of given str with <, <<, |, >>, > delimited by spaces
 * Frees str
 * str = string to copy, weakqt = 0, strongqt = 42
 */
char	*ms_add_32(char *str, int weakqt, int strongqt)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc(ms_size_32(str, 0, 42) + 1);
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		if (!ms_check_qt(str[i], &weakqt, &strongqt))
			ms_add_32_ext(str, newstr, &i, &j);
		else
			newstr[i + j] = str[i];
		i++;
	}
	newstr[i + j] = '\0';
	free(str);
	return (newstr);
}

/**
 * 25-line extension for ms_add_32
 */
static void	ms_add_32_ext(char *str, char *newstr, int *i, int *j)
{
	newstr[*i + *j] = str[*i];
	if (str[*i] != 34 && str[*i] != 39)
	{
		if (ms_check_delim(str, *i) == 1)
		{
			(*j)++;
			newstr[*i + *j] = 32;
		}
		else if (ms_check_delim(str, *i) == 2)
		{
			(*j)++;
			newstr[*i + *j] = 32;
			newstr[*i + *j + 1] = str[*i + 1];
			(*i)++;
		}
	}
}

/**
 * Returns size of str with space-delimited  <, <<, |, >>, >
 * str = string to check, weakqt = 0, strongqt = 42
 */
static int	ms_size_32(char *str, int weakqt, int strongqt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ms_check_qt(str[i], &weakqt, &strongqt))
		{
			if (ms_check_delim(str, i))
				j++;
		}
		i++;
	}
	return (ms_strlen(str) + j);
}

/**
 * Checks wether a space should follow str[i]
 * Returns 1 -> yes, 0 -> no, 2 -> yes (two chars: <<, >>)
 */
static int	ms_check_delim(char *str, int i)
{
	int	j;
	int	k;
	int	l;

	j = ms_check_delimb(str, i);
	k = 0;
	l = 0;
	if (str[i + 1])
		k = ms_check_delimb(str, i + 1);
	if (str[i + 1] && str[i + 2])
		l = ms_check_delimb(str, i + 2);
	if (j == 3 && k == 1)
		return (1);
	if (j == 3 && k == 2)
		return (2);
	if (j == 1 && k != 0)
		return (1);
	if (j == 2 && l != 0)
		return (0);
	return (0);
}

/**
 * Returns j depending on str[i] and str[i + 1]
 * 0 -> 32 or terminator
 * 1 -> <, |, >
 * 2 -> <<, >>
 * 3 -> other character
 */
static int	ms_check_delimb(char *str, int i)
{
	int	j;

	j = 0;
	if (!str[i])
		return (0);
	if (str[i] != 32)
		j = 3;
	if (str[i] == 124)
		j = 1;
	if (str[i] == 60 && str[i + 1] && str[i + 1] == 60)
		j = 2;
	else if (str[i] == 60)
		j = 1;
	if (str[i] == 62 && str[i + 1] && str[i + 1] == 62)
		j = 2;
	else if (str[i] == 62)
		j = 1;
	return (j);
}
