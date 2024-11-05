/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:41:00 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 14:27:23 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	error_exit(char *msg, int error_number)
{
	perror(msg);
	exit(error_number);
}

int	parent_process_exec(t_data *data)
{
	char	**argv;

	if (builtin_exception2(data->lstart->content->cmd[0]) \
		== 1 && is_path(data) == 1)
	{
		printf("bash: %s: ", data->lstart->content->cmd[0]);
		printf(" No such file or directory\n");
		return (127);
	}
	argv = data->lstart->content->cmd;
	if (ft_strlcmp_limited(argv[0], "export") == 0)
		return (ft_export(data, data->lstart));
	if (ft_strlcmp_limited(argv[0], "unset") == 0)
		return (ft_unset(data, data->lstart));
	if (ft_strlcmp_limited(argv[0], "cd") == 0)
		return (ft_cd(data->lstart));
	if (ft_strlcmp_limited(argv[0], "env") == 0)
		return (ft_env(data));
	if (ft_strlcmp_limited(argv[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strlcmp_limited(argv[0], "echo") == 0)
		return (ft_echo(data, data->lstart));
	return (1);
}

int	is_pipe(t_data *data)
{
	t_list	*tmp;

	tmp = data->lstart;
	while (tmp)
	{
		if (tmp->content->oper == 6)
			return (1);
		if (tmp->content->infd[0] != NULL)
			return (1);
		if (tmp->content->outfd[0] != NULL)
			return (1);
		tmp = tmp->next;
	}
	return (-1);
}

int	pipe_oper_exeption(t_data *data)
{
	if (data->lstart->content->oper != 1 && is_pipe(data) == -1 \
		&& builtin_exception(data->lstart) == 1)
	{
		g_lastexit = parent_process_exec(data);
		return (0);
	}
	return (1);
}

void	exec_command(t_data *data)
{
	int		i;
	t_list	*tmp;
	t_list	*prv_list;

	if (pipe_oper_exeption(data) == 0)
		return ;
	i = -1;
	tmp = data->lstart;
	while (tmp)
	{
		i ++;
		prv_list = prv_list_finder(data, tmp);
		display_changer(data, tmp, i);
		if ((prv_list && prv_list->content->oper == 1))
		{
			tmp = tmp->next;
			continue ;
		}
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			child_process(data, tmp, i);
		tmp = tmp->next;
	}
	parent_process(data);
}
