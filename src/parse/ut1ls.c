/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut1ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:03:12 by jbober            #+#    #+#             */
/*   Updated: 2024/10/22 17:13:53 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ms_speciasplit(t_data *data, char *str);
int		ms_check_qt(char c, int *weakqt, int *strongqt);
int		ms_envp(t_data *data, char **envp);

/**
 * Mallocs and returns the str beginning at the last slash
 * Frees the original str
*/
char	*ms_speciasplit(t_data *data, char *str)
{
	char	*newstr;
	int		i;
	int		j;

	i = ms_strlen(str) - 1;
	j = 0;
	while (str[i] && str[i] != 47)
		i--;
	newstr = malloc((ms_strlen(str) - i + 1) * sizeof(char));
	if (!newstr)
	{
		free(str);
		ms_error(data, "ut1ls.c 140: failloc :(", ENOMEM);
	}
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free (str);
	return (newstr);
}

/**
 * Checks wether char c is in weak or strong quotes
 * Modifyes qts in case of c being one
 * 0 -> in no quotes
 * 1 -> in weak quotes ""
 * 2 -> in strong quotes ''
 * c = Char to evaluate, weakqt = &weakqt, strongqt = &strongqt
 */
int	ms_check_qt(char c, int *weakqt, int *strongqt)
{
	int	i;

	i = 0;
	if (*weakqt % 2)
		i = 1;
	if (*strongqt % 2)
		i = 2;
	if (c == 34 && !(*strongqt % 2))
		(*weakqt)++;
	if (c == 39 && !(*weakqt % 2))
		(*strongqt)++;
	return (i);
}

/**
 * Initializes data->env
 */
int	ms_envp(t_data *data, char **envp)
{
	int	k;

	k = 0;
	data->env = NULL;
	while (envp[k])
		k++;
	data->env = malloc((k + 1) * sizeof(char *));
	if (!data->env)
		return (0);
	k = 0;
	while (envp[k])
	{
		data->env[k] = ms_strdup(envp[k]);
		k++;
	}
	data->env[k] = NULL;
	return (1);
}
