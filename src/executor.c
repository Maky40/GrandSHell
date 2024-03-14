/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:18:42 by xav               #+#    #+#             */
/*   Updated: 2024/03/14 09:40:15 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void open_append(t_command *command, int i)
{
	int fd;

	printf("Append file :%s\n", command->fd[i].str);
	fd = open(command->fd[i].str, O_CREAT | O_RDWR, 0777);
	if (command->fd[i].str == command->output_file)
		command->output_file_fd = fd;
	else
		close(fd);
	
}

void open_output(t_command *command, int i)
{
	int fd;
	
	printf("Output file :%s\n", command->fd[i].str);
	fd = open(command->fd[i].str, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (command->fd[i].str == command->output_file)
		command->output_file_fd = fd;
	else
		close(fd);
}

int open_input(t_command *command, t_data *data, int i)
{ 
	int fd;
	
	printf("Input file :%s\n", command->fd[i].str);
	fd = open(command->fd[i].str, O_RDONLY);
	if (fd < 0)
	{
		data->exit_status = 1;
		printf("bash: unknown: No such file or directory\n");
		return (1);
	}
	if (command->fd[i].str == command->input_file)
		command->input_file_fd = fd;
	else
		close(fd);
	return (0);
}


int open_last(t_command *command, t_data *data, int i)
{
	if (command->fd[i].token == 2)
	{
		if (open_input(command, data, i) == 1)
			return (1);
	}
	else if ((command->fd[i].token == 3))
		open_output(command, i);
	else if (command->fd[i].token == 4)
		open_append(command, i);
	return (0);
}

int open_fd(t_command *command, t_data *data)
{
	int i = 0;

	while (command->fd[i].last != 1)
	{
		if (command->fd[i].token == 2)
		{
			if (open_input(command, data, i) == 1)
				return (1);
		}
		else if ((command->fd[i].token == 3))
			open_output(command, i);
		else if (command->fd[i].token == 4)
			open_append(command, i);
		i++;
	}
	if (open_last(command, data, i) == 1)
		return (1);
	return (0);
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
	int i;

	i = 0;
	while (i < tab_cmds->num_commands)
	{
		if (open_fd(&tab_cmds->commands[i], data) == 0)
		{
			if (is_builtin(tab_cmds->commands[i].command) == 0)
				built_in_execute(&tab_cmds->commands[i], data);
			else
				execute(&tab_cmds->commands[i], data);
		}
		i++;
	}
}


