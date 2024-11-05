/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:47:33 by jbober            #+#    #+#             */
/*   Updated: 2024/10/24 14:03:05 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_lastexit;

int			main(int argc, char **argv, char **envp);
static void	ms_initialize(t_data *data, char **envp);
static int	ms_read_input(t_data *data);

static void	ms_initialize(t_data *data, char **envp)
{
	(void) envp;
	data->currinput = NULL;
	data->currstr = NULL;
	data->currmds = NULL;
	data->lstart = NULL;
	g_lastexit = 0;
	data->env = NULL;
	data->env_set = 0;
	data->new_envp = NULL;
	data->redisplay = 0;
	data->num_pipe = 0;
	data->num_envp = 0;
	data->errcode = 0;
	data->patharr = NULL;
	data->pipe = NULL;
}

int	case_exit(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i ++ ;
	if (line[i] && line[i + 1] && line[i + 2] && line[i + 3])
	{
		if (line[i] == 'e' && line[i + 1] == 'x' && line[i + 2] == 'i' \
			&& line[i + 3] == 't')
			return (1);
	}
	return (0);
}

static int	ms_read_input(t_data *data)
{
	char	*cwd;
	char	*new_cwd;

	cwd = getcwd(NULL, 0);
	new_cwd = ft_strcat(cwd, "$ ");
	if (data->redisplay == 0)
		data->currinput = readline(new_cwd);
	else
	{
		free_cwd_new(new_cwd, cwd);
		ft_putstr_fd("\n", 2);
		data->redisplay = 0;
		return (1);
	}
	data->redisplay = 0;
	free_cwd_new(new_cwd, cwd);
	if (!data->currinput)
		ms_error(data, "", 0);
	if (ms_strlen(data->currinput) != 0)
	{
		add_history(data->currinput);
		return (0);
	}
	return (1);
}

void	free_and_termination(t_data *data)
{
	terminatation(data);
	data_setting(data);
	exec_command(data);
	free_data(data);
	ms_free(data, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ms_initialize(&data, envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		ft_signal();
		if (ms_read_input(&data) == 1)
			continue ;
		if (data.env_set == 0)
			envlistmaker(&data, envp);
		envp_maker(&data);
		if (!ms_parse_ctrl(&data, envp))
		{
			g_lastexit = 1;
			ft_putstr_fd("bash: syntax error near \
			unexpected token `newline'\n", 2);
			ms_free(&data, 0);
			continue ;
		}
		free_and_termination(&data);
	}
	ms_free(&data, 1);
	return (0);
}
