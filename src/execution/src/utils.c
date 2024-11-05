/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:44:56 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 10:13:46 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*without_data(char *str)
{
	char	*newstr;
	int		i;
	int		j;

	i = ms_strlen(str) - 1;
	j = 0;
	while (str[i] && str[i] != 47)
		i--;
	newstr = malloc((ms_strlen(str) - i + 1) * sizeof(char));
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free (str);
	return (newstr);
}

void	envlist_free(t_data *data, t_envlist *head)
{
	t_envlist	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	data->env_set = 0;
}

void	free_data(t_data *data)
{
	free_pipe(data);
	free(data->pid);
	doublearr_free(&data->new_envp);
	doublearr_free(&data->patharr);
}
