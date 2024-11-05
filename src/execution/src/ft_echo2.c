/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:19:14 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/24 10:59:08 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**filearr_maker(int file_num)
{
	char	**file_arr;

	file_arr = (char **)malloc(sizeof(char *) * (file_num + 1));
	file_arr[file_num] = NULL;
	return (file_arr);
}

int	filenum_count(void)
{
	struct dirent	*t_dirent;
	DIR				*tmp;
	int				i;

	tmp = opendir(".");
	i = 1;
	t_dirent = readdir(tmp);
	while (t_dirent != NULL)
	{
		if (t_dirent->d_name[0] == '.')
		{
			t_dirent = readdir(tmp);
			continue ;
		}
		i ++;
		t_dirent = readdir(tmp);
	}
	return (i);
}

int	ft_strcmp3(const char *s1, const char *s2, int size)
{
	int	i;

	i = 0;
	if (s1[0] == '\0' || s2[0] == '\0')
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && i < size)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (1);
		i ++ ;
	}
	return (0);
}

int	all_n(char *txt, int len)
{
	int	i;

	i = 0;
	if (len <= 0 || txt == NULL)
		return (-1);
	while (i < len)
	{
		if (i >= len || txt[i] == '\0')
			break ;
		if (i > 0 && txt[i] != 'n')
			return (-1);
		i ++ ;
	}
	return (1);
}
