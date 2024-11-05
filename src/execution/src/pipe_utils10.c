/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:55:08 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 14:21:18 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	only_num_pm(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0 && (s[i] != '+' && s[i] != '-'))
			return (0);
		i ++;
	}
	return (1);
}

int	get_code(t_data *data)
{
	int	i;

	i = 0;
	if (!only_num_pm(data->lstart->content->cmd[1]))
	{
		ft_putstr_fd("numeric argument requried\n", 2);
		return (2);
	}
	while (data->lstart->content->cmd[i])
		i ++;
	if (i < 2)
		return (0);
	if (i == 2)
		return (ft_atoi(data->lstart->content->cmd[1]));
	if (i > 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	return (1);
}

int	terminatation(t_data *data)
{
	int	code;

	code = 0;
	if (case_exit(data->currinput) == 1)
	{
		code = get_code(data);
		if (code < 0)
			code = (unsigned char)code;
		g_lastexit = code;
		if (data->env_set == 1)
			envlist_free(data, data->envlist);
		exit (code);
	}
	return (0);
}

void	free_cwd_new(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int	is_path(t_data *data)
{
	t_envlist	*tmp;

	tmp = data->envlist;
	while (tmp)
	{
		if (tmp->value[0] == 'P' && tmp->value[1] == 'A' \
		&& tmp->value[2] == 'T' && tmp->value[3] == 'H' \
		&& tmp->value[4] == '=' && tmp->value[5] == '/')
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
