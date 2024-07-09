
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_classification.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:26:14 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/08 22:31:45 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++ ;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main(int argc, char *argv[])
{
	(void) argc;

	// int	i;

	// i = 0;
	// while (argv[i] != NULL)
	// {
	// 	printf("argv[%d] : %s\n", i, argv[i]);
	// 	i ++ ;
	// }
	if (ft_strcmp(argv[1], "echo") == 0)
		ft_echo(argv);
	if (ft_strcmp(argv[1], "cd") == 0)
		ft_cd(argv);
	if (ft_strcmp(argv[1], "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(argv[1], "export") == 0)
		ft_export();
	if (ft_strcmp(argv[1], "env") == 0)
		ft_env();
}