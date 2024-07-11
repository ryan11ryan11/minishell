
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

int		env_size_checker(char *env[])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i ++ ;
	return (i);
}

t_envlist	*envlist_new(void *content)
{
	t_envlist	*newlist;

	newlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (!newlist)
		return (NULL);
	newlist -> value = content;
	newlist -> next = NULL;
	return (newlist);
}

t_envlist	*ft_envlast(t_envlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}


void	envlist_addback(t_envlist **lst, t_envlist *new)
{
	t_envlist	*temp;

	temp = *lst;
	if (!new)
		return ;
	if (!temp)
	{
		(*lst) = new;
		return ;
	}
	temp = ft_envlast(*lst);
	(temp)->next = new;
}


int	envmaker(t_data *data, char *env[])
{
	int	env_size;
	int	i;
	t_envlist	*last_block;

	i = 0;
	env_size = env_size_checker(env);
	data->envlist = envlist_new(env[0]);
	if (data->envlist == NULL)
		return (FAIL);
	i = 1;
	while (i < env_size)
	{
		last_block = (t_envlist *)malloc(sizeof(t_envlist));
		envlist_addback(&data->envlist, last_block);
		last_block->value = env[i];
		i ++ ;
	}
	// while (data->envlist != NULL)
	// {
	// 	printf("%s\n",data->envlist->value);
	// 	data->envlist = data->envlist->next;
	// }
	return (SUCCESS);
}


int main(int argc, char *argv[], char *env[])
{
	(void) argc;
	t_data	data;

	envmaker(&data, env);
	if (ft_strcmp(argv[1], "echo") == 0)
		ft_echo(argv);
	if (ft_strcmp(argv[1], "cd") == 0)
		ft_cd(argv);
	if (ft_strcmp(argv[1], "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(argv[1], "export") == 0)
		ft_export(argv, data.envlist);
	if (ft_strcmp(argv[1], "env") == 0)
		ft_env();
	return (0);
}