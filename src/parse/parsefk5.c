/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:24:55 by jbober            #+#    #+#             */
/*   Updated: 2024/10/22 17:12:38 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char		*ms_parsefk5_ctrl(t_data *data, int i, int k);
static int	ms_fillnode(t_data *data, t_node *content, int i, int k);
static int	ms_addsize(t_data *data, int first, int superlast);
static int	ms_malfd(t_data *data, t_node *content, int i, int k);

/**
 * Control structure
 * Creates list with content of data->*currinput
 * Pipe or << -> new node
 * i = 0, k = 0
 */
char	*ms_parsefk5_ctrl(t_data *data, int i, int k)
{
	data->currmds = ms_lstnew(data);
	data->lstart = data->currmds;
	while (data->currstr[k])
	{
		if ((data->currstr[k][0] == 124) || (data->currstr[k][0] == 60
			&& data->currstr[k][1] && data->currstr[k][1] == 60))
		{
			if (!ms_fillnode(data, data->currmds->content, i, k))
				return (NULL);
			ms_lstadd_back(data, &data->lstart);
			data->currmds = data->currmds->next;
			i = k + 1;
		}
		k++;
	}
	if (!ms_fillnode(data, data->currmds->content, i, k))
		return (NULL);
	data->currmds->next = NULL;
	if (!ms_deqtfy_nodes(data, data->lstart))
		return (NULL);
	return ("Success");
}

/**
 * Fills node with adequate information from data->**currstr
 * first == first array for node
 * slast[superlast] == one after last array for node
 */
static int	ms_fillnode(t_data *data, t_node *content, int first, int slast)
{
	int	size;

	size = ms_addsize(data, first, slast);
	content->cmd = malloc(size * sizeof(char *));
	if (!content->cmd)
		return (0);
	content->cmd[size - 1] = NULL;
	content->infd = NULL;
	content->outfd = NULL;
	content->oper = 0;
	if (data->currstr[slast] && data->currstr[slast][0] == 60)
		content->oper = 1;
	if (data->currstr[slast] && data->currstr[slast][0] == 124)
		content->oper = 6;
	if (!ms_malfd(data, content, first, slast))
		return (0);
	if (!ms_fillnodexta(data, content, first, slast))
		return (0);
	return (1);
}

/**
 * Returns superlast - first + 1, -1 for each << in node, -2 for each <, >, >>
 */
static int	ms_addsize(t_data *data, int first, int superlast)
{
	int	size;

	size = superlast - first + 1;
	while (first < superlast)
	{
		if (data->currstr[first][0] == 60)
		{
			if (data->currstr[first][1] && data->currstr[first][1] == 60)
				size++;
			size -= 2;
		}
		if (data->currstr[first][0] == 62)
			size -= 2;
		first++;
	}
	return (size);
}

/**
 * Mallocs **infd and **outfd
 * i == first array for node/ aktuell
 * k == one after last array for node
 */
static int	ms_malfd(t_data *data, t_node *content, int i, int k)
{
	int	ninfd;
	int	noutfd;

	ninfd = 0;
	noutfd = 0;
	while (i < k)
	{
		if (data->currstr[i][0] == 60)
			ninfd++;
		if (data->currstr[i][0] == 62)
			noutfd++;
		if ((data->currstr[i][0] == 60) || (data->currstr[i][0] == 62))
			i++;
		i++;
	}
	content->infd = malloc((ninfd + 1) * sizeof(char *));
	content->outfd = malloc((noutfd + 1) * sizeof(char *));
	ms_allocstatus(content, noutfd);
	if (!content->infd || !content->outfd || !content->status)
		return (0);
	content->infd[ninfd] = NULL;
	content->outfd[noutfd] = NULL;
	return (1);
}
