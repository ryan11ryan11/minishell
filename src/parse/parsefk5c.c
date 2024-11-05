/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk5c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:00:45 by jbober            #+#    #+#             */
/*   Updated: 2024/10/23 12:39:34 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int			ms_fillnodexta(t_data *data, t_node *content, int i, int k);
static int	ms_fnb(t_data *data, t_node *content, int *i, int *ninfd);
static int	ms_fnc(t_data *data, t_node *content, int *i, int *noutfd);
static int	ms_fillinfd(t_data *data, t_node *content, int *i, int *k);
static int	ms_filloutfd(t_data *data, t_node *content, int *i, int *k);

/**
 * More than 25 lines:
 * Fills node with adequate information from data->**currstr
 * i == first array for node/ aktuell
 * k == one after last array for node
 */
int	ms_fillnodexta(t_data *data, t_node *content, int i, int k)
{
	int		c;
	int		ni;
	int		no;

	c = 0;
	ni = 0;
	no = 0;
	while (i < k)
	{
		if (data->currstr[i][0] == 60 && !ms_fnb(data, content, &i, &ni))
			return (0);
		else if (i < k && data->currstr[i][0] == 62
			&& !ms_fnc(data, content, &i, &no))
			return (0);
		else if (i < k && data->currstr[i][0] != 60
			&& data->currstr[i][0] != 62)
		{
			content->cmd[c++] = ms_strdup(data->currstr[i++]);
			if (!content->cmd[c - 1])
				return (0);
		}
	}
	return (1);
}

/**
 * More than 25 linesaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
 */
static int	ms_fnb(t_data *data, t_node *content, int *i, int *ninfd)
{
	if (data->currstr[*i][0] == 60)
	{
		if (!ms_fillinfd(data, content, i, ninfd))
			return (0);
	}
	return (1);
}

/**
 * More than 25 linesaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
 */
static int	ms_fnc(t_data *data, t_node *content, int *i, int *noutfd)
{
	if (data->currstr[*i][0] == 62)
	{
		if (!ms_filloutfd(data, content, i, noutfd))
			return (0);
	}
	return (1);
}

/**
 * Handles currstr[i] == 60
 * 	-> fills content->infd
 * k == infd[k] to fill
 * Increases i by 2, k by 1
 */
static int	ms_fillinfd(t_data *data, t_node *content, int *i, int *k)
{
	if (!data->currstr[*i + 1])
		return (0);
	content->infd[*k] = ms_cleanqt(data->currstr[*i + 1], 0, 42, 0);
	if (!content->infd[*k])
		return (0);
	(*i) += 2;
	(*k)++;
	return (1);
}

/**
 * Handles currstr[i] == 60
 * 	-> fills content->outfd
 * k == infd[k] to fill
 * Increases i by 2, k by 1
 */
static int	ms_filloutfd(t_data *data, t_node *content, int *i, int *k)
{
	if (!data->currstr[*i + 1])
		return (0);
	content->outfd[*k] = ms_cleanqt(data->currstr[*i + 1], 0, 42, 0);
	if (!content->outfd[*k])
		return (0);
	if (data->currstr[*i][1] && data->currstr[*i][1] == 62)
		content->status[*k] = 2;
	else
		content->status[*k] = 1;
	(*i) += 2;
	(*k)++;
	return (1);
}
