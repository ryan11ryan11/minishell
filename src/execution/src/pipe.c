/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:38:21 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 12:29:41 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	init_pipe(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_pipe <= 0)
		return ;
	while (i < data->num_pipe)
	{
		if (pipe(data->pipe[i]) == -1)
		{
			perror("pipe init failed");
			exit (1);
		}
		i ++ ;
	}
}

void	pipe_all_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_pipe)
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
		i ++;
	}
}

void	exec_pipe(t_data *data, t_list *list, int i)
{
	if ((list->content->oper == 0 && list->content->infd[0]) || \
	(list->content->oper == 6 && list->content->outfd[0]))
	{
		pipe_all_close(data);
		return ;
	}
	if (i == 0)
	{
		dup2(data->pipe[0][1], STDOUT_FILENO);
		pipe_all_close(data);
		return ;
	}
	if (i == data->num_pipe)
	{
		dup2(data->pipe[i - 1][0], STDIN_FILENO);
		pipe_all_close(data);
		return ;
	}
	dup2(data->pipe[i - 1][0], STDIN_FILENO);
	dup2(data->pipe[i][1], STDOUT_FILENO);
	pipe_all_close(data);
	return ;
}

void	free_pipe(t_data *data)
{
	int	i;

	i = 0;
	if (data->pipe == NULL)
		return ;
	while (i < data->num_pipe)
	{
		free(data->pipe[i]);
		i ++ ;
	}
	free(data->pipe);
}
