/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:53:32 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 10:58:57 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	child_ctrl_c(int signum)
{
	(void) signum;
	exit (130);
}

void	child_signal(void)
{
	signal(SIGINT, child_ctrl_c);
}

void	display_changer(t_data *data, t_list *list, int i)
{
	int	status;

	status = 0;
	if (list->content->infd[0] || list->content->outfd[0])
		status = 1;
	if (list->content->oper == 1 || \
		(i == 0 && ft_strlcmp_limited(list->content->cmd[0], "grep") == 0) || \
		(i == 0 && status == 0 && \
		(ft_strlcmp_limited(list->content->cmd[0], "cat") == 0) \
		&& !list->content->cmd[1]) \
		|| (i == 0 && status == 0 && \
		(ft_strlcmp_limited(list->content->cmd[0], "wc") == 0) \
		&& !list->content->cmd[1]))
		data->redisplay = 42;
}
