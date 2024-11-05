/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut3ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:40:00 by jbober            #+#    #+#             */
/*   Updated: 2024/10/22 17:14:51 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list			*ms_lstnew(t_data *data);
void			ms_lstadd_back(t_data *data, t_list **lst);
static t_list	*ms_lstlast(t_list *lst);

t_list	*ms_lstnew(t_data *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		ms_error(data, "ut3ls.c 58: failloc :(", ENOMEM);
	new->content = malloc(sizeof(t_node));
	if (!new->content)
		ms_error(data, "ut3ls.c 61: failloc :(", ENOMEM);
	new->next = 0;
	return (new);
}

void	ms_lstadd_back(t_data *data, t_list **lst)
{
	t_list	*last;
	t_list	*new;

	new = ms_lstnew(data);
	if (!new)
		ms_error(data, "ut3ls.c 73: failloc :(", ENOMEM);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ms_lstlast(*lst);
	last->next = new;
}

static t_list	*ms_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
