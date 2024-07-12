
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:35:04 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/09 11:35:04 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char path[4096];

	if (getcwd(path, 4096) != NULL)
	{
		ft_putstr_fd (path, STDOUT);
		write (1, "\n", 1);
		return (1);
	}
	return (0);
}