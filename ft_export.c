
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:28:55 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/09 12:28:55 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *msg)
{
	int	i;
	int	num_operator;

	i = 0;
	num_operator = 0;
	while (msg[i] != '\0')
	{
		if (msg[i] == '=')
			num_operator ++ ;
		i ++ ;
	}
	if (num_operator < 1)
		return (FAIL);
	return (SUCCESS);
}

int	is_duplicate(char *msg, t_envlist *envlist)
{
	t_envlist *tmp;

	tmp = envlist;
	while (tmp != NULL)
	{
		if (ft_strcmp(envlist->value, msg) == 0)
		{
			envlist->value = msg;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (FAIL);
}

int	is_special(char *msg)
{
	int	i;

	i = 0;
	if ('0' <= msg[0] || msg[0] <= '9')
		return (FAIL);
	while (msg[i] != '\0')
	{
		if (!ft_isalnum(msg[i]) && msg[i] != '_' && msg[i] != '=')
			return (FAIL);
		i ++ ;
	}
	return (SUCCESS);
}

void	print_all(t_envlist *envlist)
{
	while (envlist != NULL)
	{
		//printf("declare -x %s\n",envlist->value);
		ft_putstr_fd ("declare -x ", STDOUT);
		ft_putstr_fd (envlist->value, STDOUT);
		write(1, "\n", STDOUT);
		envlist = envlist->next;
	}

}

int	validity_check(char *msg, t_envlist *envlist)
{
	if (msg == NULL)
	{
		print_all(envlist);
		return (FAIL);
	}
	if (is_operator(msg) == FAIL)
		return (FAIL);
	if (is_duplicate(msg, envlist) == SUCCESS)
		return (SUCCESS);
	if (is_special(msg) == FAIL)
	{
		ft_putstr_fd ("not a valid identifier\n", STDERR);
		return (FAIL);
	}
	return (SUCCESS);
}

int	ft_export(char *argv[], t_envlist *envlist)
{
	t_envlist	*new;

	if (validity_check(argv[2], envlist) == FAIL)
		return (FAIL);
	new = (t_envlist *)malloc(sizeof(t_envlist));
	new->value = argv[2];
	envlist_addback(&envlist, new);
	// while (envlist != NULL)
	// {
	// 	printf("%s\n",envlist->value);
	// 	envlist = envlist->next;
	// }
	return (1);
}