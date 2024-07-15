/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:17:53 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/15 14:07:13 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	t_envlist	*tmp;
	
	tmp = data->envlist;
	while (tmp != NULL)
	{
		printf("%s\n",tmp->value);
		tmp = tmp->next;
	}
}