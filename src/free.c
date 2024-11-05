/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:03:10 by jbober            #+#    #+#             */
/*   Updated: 2024/10/24 12:08:00 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ms_free(t_data *data, int modus);
static void	ms_free_currstr(t_data *data);
static void	ms_free_env(t_data *data);
static void	ms_free_lst(t_list **iamhere);
static void	ms_free_node(char **str);

/**
 * Frees everything that is bound in shackles, longing for the taste of freedom!
 * modus 1 == clear_history (only at exit)
*/
void	ms_free(t_data *data, int modus)
{
	if (data->currinput)
	{
		free(data->currinput);
		data->currinput = NULL;
	}
	ms_free_currstr(data);
	ms_free_lst(&data->lstart);
	ms_free_env(data);
	if (modus == 1)
	{
		clear_history();
	}
}

/**
 * Frees data->currstr
*/
static void	ms_free_currstr(t_data *data)
{
	int	k;

	k = 0;
	if (data->currstr)
	{
		while (data->currstr[k])
		{
			free(data->currstr[k]);
			data->currstr[k] = NULL;
			k++;
		}
		free(data->currstr);
		data->currstr = NULL;
	}
}

/**
 * Frees data->env && data->cstrl
 * k == 0
 */
static void	ms_free_env(t_data *data)
{
	int	k;

	k = 0;
	if (data->env)
	{
		while (data->env[k])
		{
			free(data->env[k]);
			data->env[k] = NULL;
			k++;
		}
		free(data->env);
		data->env = NULL;
	}
}

/**
 * Frees str** in node
 */
static void	ms_free_node(char **str)
{
	int	k;

	k = 0;
	if (!str)
		return ;
	while (str[k])
	{
		free(str[k]);
		str[k] = NULL;
		k++;
	}
	free(str);
	str = NULL;
}

/**
 * frees the list \o/
 */
static void	ms_free_lst(t_list **iamhere)
{
	t_list	*tmp;

	if (!iamhere || !*iamhere)
		return ;
	tmp = *iamhere;
	if (tmp->content)
	{
		ms_free_node(tmp->content->cmd);
		ms_free_node(tmp->content->infd);
		ms_free_node(tmp->content->outfd);
		free(tmp->content->status);
		free(tmp->content);
		tmp->content = NULL;
	}
	*iamhere = tmp->next;
	free(tmp);
	tmp = NULL;
	ms_free_lst(iamhere);
}
