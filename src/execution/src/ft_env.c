/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:46:30 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/17 14:10:32 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_env(t_data *data)
{
	t_envlist	*tmp;

	tmp = data->envlist;
	if (data->lstart->content->cmd[1])
	{
		ft_putstr_fd("env: No such file or directory\n", 2);
		return (127);
	}
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->value, '=') != NULL)
		{
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
