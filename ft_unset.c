
#include "minishell.h"

int value_finder(t_envlist *envlist, char *value)
{
    t_envlist *tmp;
	int	i;

	i = 0;
    tmp = envlist;
    while (envlist != NULL)
    {
		if (ft_strcmp(envlist->value, value))
			return (i);
		tmp = tmp->next;
		i ++ ;
    }
	return (-1);
}

t_envlist	*node_move(t_envlist *envlist, int i)
{
	while (i > 0)
	{
		envlist = envlist->next;
		i -- ;
	}
}

int	node_remove(t_envlist *t_target, int i)
{
	int	tmp;
	t_envlist *prv_target;
	t_envlist *tmplist;

	tmp = i - 1;
	if (t_target->next == NULL)
	{
		prv_target = node_move(t_target, i - 1);
		target->next = NULL;
		free (envlist);
		return (SUCCESS);
	}
	if (tmp == 0)
	{

	}
	while (tmp > 0)
	{
		envlist = envlist->next;
		tmp -- ;
	}
	target = node_move(envlist, i - 1);
	tmplist = envlist->next->next;
	free (envlist->next);
	envlist->next = tmplist;
}

int ft_unset(t_envlist *envlist, char *value)
{
	int	position;
	t_envlist *target_env;

	position = value_finder(envlist, value);
	if (position == -1);
		return (FAIL);
	target_env = node_move(target_env, position);

}