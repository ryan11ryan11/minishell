/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:25:22 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 14:18:47 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	path_check(t_list *list, int i)
{
	char	*word;

	word = list->content->cmd[0];
	if (!word || !word[0])
		return (1);
	if (word[0] == '/' || (word[1] && (word[0] == '.' && word[1] == '/')) || \
		((word[1] && word[2]) && (word[0] == '.' && word[1] == '.' \
			&& word[2] == '/')))
	{
		if (access(list->content->cmd[0], X_OK) == 0)
			return (0);
		else
		{
			write(2, "bash: ", 6);
			write(2, list->content->cmd[0], ft_strlen(list->content->cmd[i]));
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
	}
	return (1);
}

void	node_work(t_data *data, t_list *crt_node, int i)
{
	t_list	*prv_list;

	prv_list = NULL;
	prv_list = prv_list_finder(data, crt_node);
	if (prv_list && prv_list->content->oper == 1)
		exit (0);
	if (crt_node->content->infd != NULL)
		case_infile(crt_node);
	if (crt_node->content->outfd != NULL)
		case_outfile(crt_node->content);
	if (crt_node->content->oper == 1)
		case_heredoc(data, crt_node);
	if ((crt_node->content->oper == 6) || \
	(prv_list && prv_list->content->oper == 6))
		exec_pipe(data, crt_node, i);
}

void	child_process(t_data *data, t_list *crt_node, int i)
{
	char	*command;
	char	*path;

	command = NULL;
	all_component_check2(crt_node, data, i);
	if (crt_node->content->oper != 1 && \
	(!crt_node || !crt_node->content->cmd || !crt_node->content->cmd[0] || \
	(!crt_node->content->cmd[0][0] && crt_node->content->oper != 1)))
		return ;
	node_work(data, crt_node, i);
	if (crt_node->content->cmd[0])
		command = crt_node->content->cmd[0];
	else
		exit(0);
	builtin_situation(data, crt_node);
	path = pathfinder(command, data);
	if (!path)
		error_exit(command, 1);
	if (path && (char *const *)crt_node->content->cmd && data->new_envp)
	{
		envp_maker(data);
		execve(path, (char *const *)crt_node->content->cmd, data->new_envp);
		exit_diff_code(errno);
	}
}

void	parent_process(t_data *data)
{
	int	j;
	int	status;
	int	exit_code;

	j = 0;
	status = 0;
	while (j < data->num_pipe)
	{
		close(data->pipe[j][0]);
		close(data->pipe[j][1]);
		j ++;
	}
	j = 0;
	while (j < data->num_ndata)
	{
		waitpid(data->pid[j], &status, 0);
		j ++;
	}
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		g_lastexit = exit_code;
	}
}

int	exec_command_errcheck(t_data *data)
{
	t_node	*argvt;

	argvt = data->lstart->content;
	if (data->lstart->content->cmd[0][0] == '\0')
		return (-1);
	if (ft_get_env(data) == NULL && \
	ft_strlcmp_limited(argvt->cmd[0], "export") != 0)
	{
		g_lastexit = 127;
		ft_putstr_fd("command not found\n", 1);
		return (-1);
	}
	return (1);
}
