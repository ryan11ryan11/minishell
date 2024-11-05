/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:24:42 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 12:45:22 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	heredoc_read(t_heredoc *hrd)
{
	while (1)
	{
		write(1, "> ", 2);
		hrd->byte_read = read(STDIN_FILENO, hrd->buffer + hrd->total_byte, \
		sizeof(hrd->buffer) - hrd->total_byte - 1);
		if (hrd->byte_read <= 1)
		{
			hrd->total_byte = 0;
			continue ;
		}
		hrd->total_byte = hrd->total_byte + hrd->byte_read;
		hrd->last_word = get_last_word(hrd->buffer, hrd->total_byte - 1);
		if (ft_strlcmp_limited(hrd->delimiter, hrd->last_word) == 0)
			break ;
		free(hrd->last_word);
	}
	hrd->buffer[hrd->total_byte - 1 - ft_strlen(hrd->last_word)] = '\0';
	close(hrd->fd[0]);
	write(hrd->fd[1], hrd->buffer, ft_strlen(hrd->buffer));
	close(hrd->fd[1]);
	free(hrd->last_word);
	free(hrd);
	exit (0);
}

void	case_heredoc(t_data *data, t_list *list)
{
	t_heredoc	*hrd;

	child_signal();
	heredoc_struc_init(data, list);
	hrd = data->heredoc;
	if (hrd && hrd->delimiter == NULL)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		exit(2);
	}
	pipe(hrd->fd);
	hrd->pid = fork();
	if (hrd->pid == 0)
		heredoc_read(hrd);
	else
		heredoc_parent(hrd->fd, hrd->pid);
}

int	case_infile(t_list *list)
{
	int		fd;
	int		i;

	i = 0;
	while (list->content->infd[i])
	{
		fd = open(list->content->infd[i], O_RDONLY);
		if (fd == -1)
		{
			perror("Error:");
			exit (1);
		}
		dup2(fd, STDIN_FILENO);
		close (fd);
		i ++;
	}
	return (0);
}

t_list	*prv_list_finder(t_data *data, t_list *current_node)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = data->lstart;
	prev = NULL;
	while (tmp)
	{
		if (tmp == current_node)
			return (prev);
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

void	exit_diff_code(int code)
{
	if (code == 13)
		error_exit("Is a directory", 126);
	error_exit("Error", code);
}
