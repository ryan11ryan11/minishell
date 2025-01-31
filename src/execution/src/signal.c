/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:31:40 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/23 20:54:57 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	set_terminal_print_on(void)
{
	struct termios	terminal_info;

	tcgetattr(1, &terminal_info);
	terminal_info.c_lflag |= (ECHOCTL);
	tcsetattr(1, 0, &terminal_info);
}

void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	ctrl_c(int signum)
{
	(void) signum;
	g_lastexit = 130;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(void)
{
	set_terminal_print_off();
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
