/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut4ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:40:44 by rakropp           #+#    #+#             */
/*   Updated: 2024/10/22 13:51:44 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char		*ms_itoa(int n);
static int	intlen(int n);
int			ms_cinset(char c, char *set, int modus);

char	*ms_itoa(int n)
{
	char	*ret;
	int		len;

	len = intlen(n);
	if (n == -2147483648)
		return (ms_strdup("-2147483648"));
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	if (n == 0)
		*ret = '0';
	if (n < 0)
	{
		n *= -1;
		*ret = '-';
	}
	ret[len--] = '\0';
	while (n)
	{
		ret[len--] = (n % 10) + 48;
		n = n / 10;
	}
	return (ret);
}

static int	intlen(int n)
{
	int	ret;

	ret = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		ret++;
		n *= -1;
	}
	while (n)
	{
		n = n / 10;
		ret++;
	}
	return (ret);
}

/**
 * Checks wether char c is contained in char *set
 * Modus 1 -> include '\0'
 * Returns 1 for yes, 0 for no
 */
int	ms_cinset(char c, char *set, int modus)
{
	int	i;

	i = 0;
	if (modus == 1)
	{
		if (!c)
			return (1);
	}
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
