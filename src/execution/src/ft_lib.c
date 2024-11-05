/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:38:58 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 13:35:22 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	size_t	word_len;
	int		i;

	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!s || !lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			lst[i++] = ft_substr(s, 0, word_len);
			s += word_len;
		}
	}
	lst[i] = NULL;
	return (lst);
}

void	ft_putstr_fd(const char *s, int fd)
{
	while (*s)
		write(fd, s++, sizeof(char));
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count] != '\0')
		++count;
	return (count);
}

char	*ft_strchr(const char *s, int ch)
{
	unsigned char	c;

	c = (unsigned char)ch;
	while (*s != c && *s != '\0')
		++s;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
