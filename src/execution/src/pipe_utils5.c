/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:34:41 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/21 17:35:07 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

pid_t	*assign_pid(int num_args)
{
	pid_t	*new_pid;
	int		i;

	i = 0;
	new_pid = (pid_t *)malloc(sizeof(pid_t) * num_args);
	if (!new_pid)
		return (NULL);
	while (i < num_args)
	{
		new_pid[i] = -1;
		i ++ ;
	}
	return (new_pid);
}

char	*absolute_path(t_data *data)
{
	t_node	*argvt;

	argvt = data->lstart->content;
	if (argvt->cmd[0][0] != '.' && argvt->cmd[0][0] != '/')
		return (NULL);
	if (access(argvt->cmd[0], X_OK) == 0)
		return ((char *)argvt->cmd[0]);
	return (NULL);
}
