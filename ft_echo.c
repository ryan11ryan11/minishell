
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:17:16 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/08 22:28:17 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *argv[])
{
	int	option;
	int	i;

	i = 2;
	option = 0;
	while (argv[i] != NULL)
	{
		if (ft_strcmp(argv[i], "-n") == 0)
		{
			i ++ ;
			option = 1;
		}
		if (argv[i] == NULL)
			return ;
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			write (1, " ", 1);
		i ++ ;
	}
	if (option == 0)
		write (1, "\n", 1);

}

