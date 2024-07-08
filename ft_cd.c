
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:12:24 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/08 22:39:48 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *argv[])
{	
	char path[100];
	
	(void) argv;
	getcwd(path, 50);
	printf("before :: %s\n", path);
	chdir("/home/junhhong/Documents/minishell/222");
	getcwd(path,50);
	printf("after :: %s\n", path);
}

