/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:07:35 by mnie              #+#    #+#             */
/*   Updated: 2024/04/02 11:29:15 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_data *data, t_table *cmd)
{
	(void) cmd;
	/*
	if (cmd != NULL)
		free_table_cmd(cmd);
	*/
	free_data_end(data);
	ft_putstr("exit\n");
	exit (0);
}
