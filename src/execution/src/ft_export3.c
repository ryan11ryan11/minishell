/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:23:27 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/23 20:51:35 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*remove_quo(char *arr)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	j = 0;
	i = 0;
	new = NULL;
	if (ft_strchr(arr, '"') != NULL || ft_strchr(arr, '\'') != NULL)
	{
		len = ft_strlen(arr) - 2;
		new = (char *)malloc(sizeof(char) * (len + 1));
		new[len] = '\0';
		while (arr[i])
		{
			while (arr[i] == '"' || arr[i] == '\'')
				i ++ ;
			new[j] = arr[i];
			i ++ ;
			j ++ ;
		}
		free (arr);
	}
	return (new);
}

void	fix_arr(char **arr)
{
	int		i;
	char	*new;

	i = 0;
	while (arr[i] != NULL)
	{
		if (ft_strchr(arr[i], '"') != NULL || ft_strchr(arr[i], '\'') != NULL)
		{
			new = remove_quo(arr[i]);
			arr[i] = new;
		}
		i ++ ;
	}
}

void	ft_envlist_back(t_envlist **lst, t_envlist *new)
{
	t_envlist	*last;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

int	name_check(char *arr)
{
	char	**input;

	input = ft_split(arr, '=');
	if (!input)
		return (-1);
	if (underbar_alphabet(input[0]) == -1 || \
		is_empty(input[0]) == -1 || \
		is_alphabet(arr) == 1)
	{
		doublearr_free(&input);
		return (-1);
	}
	doublearr_free(&input);
	return (1);
}
