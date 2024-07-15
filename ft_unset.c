/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:37:12 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/15 13:45:01 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int value_finder(t_envlist *envlist, char *value)
{
	t_envlist *tmp;
	int	len;
	int	i;

	i = 0;
	tmp = envlist;
	len = ft_strlen(value);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->value, value, len) == 0 \
		&& tmp->value[len] == '=')
			return (i);
		tmp = tmp->next;
		i ++ ;
	}
	printf("done\n");
	return (FAIL);
}

t_envlist	*node_move(t_envlist *envlist, int i)
{
	t_envlist	*tmp;

	tmp = envlist;
	while (i > 0 && tmp != NULL)
	{
		tmp = tmp->next;
		i -- ;
	}
	return (tmp);
}

int	node_remove(t_data *data, int i)
{
	t_envlist *prv_target;
	t_envlist *target;

	target = node_move(data->envlist, i);
	prv_target = node_move(data->envlist, i - 1);
	if (target == data->envlist)
	{
		data->envlist = data->envlist->next;
		free (target);
		return (SUCCESS);
	}
	if (target->next == NULL)
	{
		prv_target->next = NULL;
		free (target);
		return (SUCCESS);
	}
	else
	{
		prv_target->next = target->next;
		free(target);
		return (SUCCESS);
	}
}

int ft_unset(t_data *data, char *argv[])
{
	int	position;
	t_envlist *target_env;
	t_envlist *tmp;

	tmp = data->envlist;
	if (!argv[2])
	{
		ft_putstr_fd ("unset: not enough arguments\n", STDERR);
		return (FAIL);
	}
	position = value_finder(data->envlist, argv[2]);
	if (position == FAIL) // does not exist
		return (FAIL);
	target_env = node_move(data->envlist, position);
	node_remove(data, position);
	tmp = data->envlist;
	// while (tmp != NULL)
	// {
	// 	printf("%s\n",tmp->value);
	// 	tmp = tmp->next;
	// }
	return (SUCCESS);
}
