/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:18:42 by xav               #+#    #+#             */
/*   Updated: 2024/03/08 16:00:22 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute(t_command *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf ("Je suis execute\n");
}

void	built_in_execute(t_command *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf("je suis built_in execute\n");
}

int	is_builtin(char *cmd)
{
	(void)cmd;
	printf("Je suis is_builtin\n");
	return (0);
}

void executor(t_table *tab_cmds, t_data *data)
{
	int	i; 

	i = 0;

	while (i < tab_cmds->num_commands)
	{
		if (is_builtin(tab_cmds->commands[i].command) == 0)
			built_in_execute(&tab_cmds->commands[i], data);
		else
			execute(&tab_cmds->commands[i], data);
	}
}
