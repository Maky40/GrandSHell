/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:18:42 by xav               #+#    #+#             */
/*   Updated: 2024/03/09 13:14:59 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_command(char *str, char *cmd)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			str++; 
		if (*str != *cmd)
			return (1);
		str++;
	}
	return (0);
}

void execute(t_command *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf ("Je suis execute\n");
}

void	built_in_execute(t_command *cmd, t_data *data)
{
	(void)data;
	if (check_command(cmd->command, "echo"))
		printf("echo\n");
	else if (check_command(cmd->command, "unset"))
		printf("unset\n");
	else if (check_command(cmd->command, "cd"))
		printf("cd\n");
	else if (check_command(cmd->command, "exit"))
		printf("exit\n");
	else if (check_command(cmd->command, "pwd"))
		printf("pwd\n");
	else if (check_command(cmd->command, "env"))
		printf("env\n");
	else if (check_command(cmd->command, "export"))
		printf("export\n");
}

int	is_builtin(char *cmd)
{
	if (check_command(cmd, "echo"))
		return (0);
	else if (check_command(cmd, "unset"))
		return (0);
	else if (check_command(cmd, "cd"))
		return (0);
	else if (check_command(cmd, "exit"))
		return (0);
	else if (check_command(cmd, "pwd"))
		return (0);
	else if (check_command(cmd, "env"))
		return (0);
	else if (check_command(cmd, "export"))
		return (0);
	return (1);
}

void executor(t_table *tab_cmds, t_data *data)
{
	int	i; 

	i = 0;
	if (tab_cmds->num_commands == 1)
	{
		if (tab_cmds->commands[0].input_file == NULL)
			tab_cmds->commands[0].input_file = STDIN_FILENO;
		if (tab_cmds->commands[0].output_file == NULL)
			tab_cmds->commands[0].input_file = STDOUT_FILENO;
	}
	else if (tab_cmds->num_commands > 1)
	{
		if (tab_cmds->commands[tab_cmds->num_commands - 1].output_file ==  NULL)
			tab_cmds->commands[tab_cmds->num_commands - 1].output_file = STDOUT_FILENO;
			
	}
	while (i < tab_cmds->num_commands)
	{
		if (is_builtin(tab_cmds->commands[i].command) == 0)
			built_in_execute(&tab_cmds->commands[i], data);
		else
			execute(&tab_cmds->commands[i], data);
	}
}
