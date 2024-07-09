/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:17:53 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/09 13:47:23 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(void)
{
	extern char **environ;

	int i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n",environ[i]);
		i ++ ;
	}
}