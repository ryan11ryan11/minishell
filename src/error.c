/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:34:33 by jbober            #+#    #+#             */
/*   Updated: 2024/10/24 13:53:40 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_error(t_data *data, char *str, int brexit);
void	ms_error_woexit(t_data *data, int brexit);

/**
 * Prints error message, frees everything and exits with error
 * str = "FILE/LINE ERRORTYPE :(", Errortypes being: failloc, invalid argument:
*/
void	ms_error(t_data *data, char *str, int brexit)
{
	(void) str;
	if (data->env_set == 1)
		envlist_free(data, data->envlist);
	set_terminal_print_on();
	ms_free(data, 1);
	errno = brexit;
	exit(brexit);
}

/**
 * Frees stuff, qui
 */
void	ms_error_woexit(t_data *data, int brexit)
{
	ms_free(data, 0);
	errno = brexit;
	g_lastexit = brexit;
}
