/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:18:42 by xav               #+#    #+#             */
/*   Updated: 2024/03/11 14:17:35 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int open_input(t_command *command)
{
	int i = 0;
	int fd; 

	while (!&command->fd[i] && command->fd->last != 1)
	{
		if (command->fd[i].token == 2)
		{
			fd = open(command->fd[i].str, O_RDONLY);
			if (fd < 0)
			{
				printf("bash: unknown: No such file or directory\n");
				return (1);
			}
		}
	}
}

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
	int		i;
	int 	fd[2];
	pid_t	child;


	while (i < tab_cmds->num_commands)
	{
		while (open_input(&tab_cmds->commands[i]) != 0)
			i++;	
		if (is_builtin(tab_cmds->commands[i].command) == 0)
			built_in_execute(&tab_cmds->commands[i], data);
		else
			execute(&tab_cmds->commands[i], data);
		
		i++;
	}
}
