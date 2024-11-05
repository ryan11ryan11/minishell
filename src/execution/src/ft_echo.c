/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:01:32 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/21 14:19:21 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**filename_arr_maker(DIR *dir)
{
	struct dirent	*t_dirent;
	char			**file_name_arr;
	int				file_num;
	int				i;

	i = 0;
	file_num = filenum_count();
	file_name_arr = filearr_maker(file_num);
	t_dirent = readdir(dir);
	while (t_dirent != NULL)
	{
		if (t_dirent->d_name[0] == '.')
		{
			t_dirent = readdir(dir);
			continue ;
		}
		file_name_arr[i] = ft_strdup(t_dirent->d_name);
		i ++;
		t_dirent = readdir(dir);
	}
	if (i == 0)
		return (NULL);
	file_name_arr[i] = NULL;
	closedir(dir);
	return (file_name_arr);
}

int	print_directory(void)
{
	DIR				*dir;
	char			**filename_arr;
	int				i;

	i = 0;
	dir = opendir(".");
	if (!dir)
	{
		perror("Error:");
		return (1);
	}
	filename_arr = filename_arr_maker(dir);
	while (filename_arr[i] != NULL)
	{
		ft_putstr_fd(filename_arr[i], 1);
		write(1, " ", 1);
		i ++;
	}
	return (0);
}

int	print_argv(t_node *argvt, int i)
{
	while (argvt->cmd[i] != NULL)
	{
		if (ft_strlcmp_limited(argvt->cmd[i], "*") == 0)
		{
			i ++ ;
			print_directory();
		}
		if (argvt->cmd[i] == NULL)
			return (1);
		ft_putstr_fd(argvt->cmd[i], 1);
		if (argvt->cmd[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i ++ ;
	}
	return (0);
}

char	**argv_maker(char *line)
{
	char	**argv;

	argv = ft_split(line, ' ');
	return (argv);
}

int	ft_echo(t_data *data, t_list *list)
{
	int		option;
	int		i;
	int		len;
	char	**argva;

	i = 1;
	option = 0;
	if (!list->content->cmd[1])
		return (0);
	argva = argv_maker(data->currinput);
	len = ft_strlen(argva[i]);
	while (list->content->cmd[i] && all_n(list->content->cmd[i], len) \
	== 1 && (ft_strcmp3(list->content->cmd[i], "-n", 2) == 0))
	{
		i ++ ;
		len = ft_strlen(argva[i]);
		option = 1;
	}
	print_argv(list->content, i);
	if (option == 0)
		write (1, "\n", 1);
	doublearr_free(&argva);
	return (0);
}
