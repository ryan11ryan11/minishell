/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:21:59 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/23 21:42:32 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	add_newblock(t_envlist **envlist, char *content)
{
	t_envlist	*new;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (!new)
	{
		perror("malloc allocation failed");
		return (-1);
	}
	new->value = ft_strdup(content);
	ft_envlist_back(envlist, new);
	g_lastexit = 0;
	return (1);
}

int	is_duplicate(char *name, t_envlist *envlist, char *arr)
{
	t_envlist	*tmp;
	char		**input;

	tmp = envlist;
	while (tmp != NULL)
	{
		input = ft_split(tmp->value, '=');
		if (!input[0] || !input)
			return (0);
		if (ft_strlcmp_limited(input[0], name) == 0)
		{
			if (ft_strchr(arr, '=') != NULL)
			{
				free(tmp->value);
				tmp->value = ft_strdup(arr);
				g_lastexit = 0;
			}
			doublearr_free(&input);
			return (-1);
		}
		doublearr_free(&input);
		tmp = tmp->next;
	}
	return (0);
}

int	is_alphabet(char *name)
{
	if ('0' <= name[0] && name[0] <= '9')
	{
		ft_putstr_fd ("export: not a valid identifier\n", 2);
		g_lastexit = 1;
		return (1);
	}
	return (-1);
}

int	is_empty(char *msg)
{
	if (msg == NULL || msg[0] == '\0')
	{
		ft_putstr_fd ("export: not a valid identifier\n", 2);
		g_lastexit = 1;
		return (-1);
	}
	return (1);
}

int	underbar_alphabet(char *msg)
{
	int	i;

	i = 0;
	while (msg[i] != '\0')
	{
		if (!((msg[0] >= 'A' && msg[0] <= 'Z') || \
		(msg[0] >= 'a' && msg[0] <= 'z')))
		{
			g_lastexit = 1;
			ft_putstr_fd ("export: not a valid identifier\n", 2);
			return (-1);
		}
		if ((msg[i] >= 'A' && msg[i] <= 'Z') \
		|| (msg[i] >= 'a' && msg[i] <= 'z') \
		|| msg[i] == '_' || ((msg[i] >= '0' && msg[i] <= '9') || msg[i] == ' '))
			i ++ ;
		else
		{
			g_lastexit = 1;
			ft_putstr_fd ("export: not a valid identifier\n", 2);
			return (-1);
		}
	}
	return (1);
}
