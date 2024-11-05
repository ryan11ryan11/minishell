/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:02 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 13:05:56 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_all_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("cmd[%d]:%s\n", i, cmd[i]);
		i ++ ;
	}
}

void	test_print(t_data *data)
{
	t_list	*tmp;
	int		k;

	tmp = data->lstart;
	while (tmp)
	{
		printf("******************************************************\n");
		printf("oper:	%d\t\n", tmp->content->oper);
		print_all_cmd(tmp->content->cmd);
		k = 0;
		while (tmp->content->infd[k])
		{
			printf("infd[%i]:	%s\n", k, tmp->content->infd[k]);
			k++;
		}
		k = 0;
		while (tmp->content->outfd[k])
		{
			printf("outfd[%i]:	%s\n", k, tmp->content->outfd[k]);
			printf("status[%i]:	%i\n", k, tmp->content->status[k]);
			k++;
		}
		tmp = tmp->next;
	}
	printf("******************************************************\n");
}
