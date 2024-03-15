/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:12:30 by xav               #+#    #+#             */
/*   Updated: 2024/03/14 15:20:39 by xav              ###   ########.fr       */
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
	int i;

	i = 0;
	if (command->no_fd == 1)
		return (0);
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