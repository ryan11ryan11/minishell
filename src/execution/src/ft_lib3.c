/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:34:18 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/21 17:34:31 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	str_len;

	if (!s)
		return (0);
	str_len = ft_strlen((char *)s);
	if (start > str_len)
		return (ft_strdup(""));
	if (str_len - start >= len)
		str = (char *)malloc((len + 1) * sizeof(char));
	else
		str = (char *)malloc((str_len - start + 1) * sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, (s + start), (len + 1));
	return (str);
}
