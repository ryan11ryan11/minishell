/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:13:59 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/23 16:57:12 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_data	data;
	char	*input;

	(void) argc;
	while(1)
	{
		input = readline("Minishell:");
		add_history(input);
		envmaker(&data, env);
		free(input);
	}
	// while (data.envlist->next != NULL)
	// {
	// 	printf("%s\n",data.envlist->value);
	// 	data.envlist = data.envlist->next;
	// }
	builtin(argv, data);
}
