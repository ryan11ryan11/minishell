/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:24:19 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 13:47:26 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	case_outfile(t_node *argvt)
{
	int	fd;
	int	i;

	i = 0;
	if (!argvt || !argvt->outfd[i])
		return ;
	while (argvt->outfd[i])
	{
		if (argvt->status && argvt->status[i] == 1)
			fd = open(argvt->outfd[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(argvt->outfd[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("Error:");
			exit (1);
		}
		i ++;
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

char	*get_last_word(char *buffer, int index)
{
	char	**split;
	char	*last;
	char	*tmp;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	tmp = ft_strdup(buffer);
	if (!tmp)
		return (NULL);
	tmp[index] = '\0';
	split = ft_split(tmp, '\n');
	if (!split)
	{
		free(tmp);
		return (NULL);
	}
	while (split[i + 1] != NULL)
		i ++;
	last = ft_strdup(split[i]);
	doublearr_free(&split);
	free(tmp);
	return (last);
}

void	heredoc_parent(int *fd, int pid)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
}

void	heredoc_struc_init(t_data *data, t_list *list)
{
	data->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	data->heredoc->total_byte = 0;
	data->heredoc->byte_read = 0;
	if (list)
		data->heredoc->delimiter = list->next->content->cmd[0];
	data->heredoc->last_word = NULL;
	ft_memset(data->heredoc->buffer, 0, 2048);
}
