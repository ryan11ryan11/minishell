/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:47:21 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 13:31:23 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	suitablity_check(char **arr)
{
	int	i;

	i = 1;
	while (arr[i])
	{
		if (name_check(arr[i]) != -1)
			return (0);
		else
			return (-1);
		i ++ ;
	}
	return (1);
}

char	*quo_add(char *arr)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	len = ft_strlen(arr);
	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (len + 3));
	new[len + 2] = '\0';
	while (i < len + 1)
	{
		new[i] = arr[j];
		if (ft_strchr(new, '"') == NULL && arr[j] == '=')
		{
			i ++ ;
			new[i] = '"';
		}
		i ++ ;
		j ++ ;
	}
	new[i] = '"';
	new[i + 1] = '\0';
	return (new);
}

void	print_all(t_envlist *envlist)
{
	t_envlist	*tmp;
	char		*new;

	tmp = envlist;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->value, '=') != NULL)
		{
			new = quo_add(tmp->value);
			ft_putstr_fd ("declare -x ", 1);
			ft_putstr_fd (new, 1);
			ft_putstr_fd ("\n", 1);
			tmp = tmp->next;
			free (new);
			continue ;
		}
		ft_putstr_fd ("declare -x ", 1);
		ft_putstr_fd (tmp->value, 1);
		ft_putstr_fd ("\n", 1);
		tmp = tmp->next;
	}
}

int	export_add(t_data *data, t_list *list)
{
	int		i;
	char	**name;

	i = 1;
	if (!list || !list->content->cmd || !list->content->cmd[0] || \
		!list->content->cmd[1])
		return (1);
	while (list->content->cmd[i])
	{
		name = ft_split(list->content->cmd[i], '=');
		if (is_duplicate(name[0], data->envlist, list->content->cmd[i]) != -1)
			add_newblock(&data->envlist, list->content->cmd[i]);
		i ++;
		doublearr_free(&name);
	}
	return (0);
}

int	ft_export(t_data *data, t_list *list)
{
	if (list->content->cmd[1] && list->content->cmd[1][0] == '=')
	{
		ft_putstr_fd("export: '=': not a valid identifier\n", 2);
		return (1);
	}
	if (list->content->cmd[1] == NULL)
	{
		print_all(data->envlist);
		return (0);
	}
	if (suitablity_check(list->content->cmd))
		return (1);
	if (export_add(data, list) == 1)
		return (1);
	envp_maker(data);
	return (0);
}
