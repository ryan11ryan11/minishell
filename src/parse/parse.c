/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:04:31 by jbober            #+#    #+#             */
/*   Updated: 2024/10/22 16:15:13 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ms_parse_ctrl(t_data *data, char **envp);

/**
 * Control structure
 * Turns the input *str data->currinput into a list (delimiter "|"), containing
 * 		a **str seperating each item (commands, arguments), infd, outfd and
 * 		*path, if applicable
 */
char	*ms_parse_ctrl(t_data *data, char **envp)
{
	if (!(ms_envp(data, envp)))
		return (NULL);
	if (!(ms_parsefk1_ctrl(data)))
		return (NULL);
	if (!(ms_parsefk2_ctrl(data)))
		return (NULL);
	if (!(ms_parsefk4_ctrl(data)))
		return (NULL);
	if (!(ms_parsefk5_ctrl(data, 0, 0)))
		return (NULL);
	return ("Success");
}
