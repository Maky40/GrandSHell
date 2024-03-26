/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:12:30 by xav               #+#    #+#             */
/*   Updated: 2024/03/24 10:42:14 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_append(t_command *command, int i)
{
	int	fd;

	printf("Append file :%s\n", command->fd[i].str);
	fd = open(command->fd[i].str, O_CREAT | O_RDWR, O_APPEND, 0777);
	close(fd);
}

void	open_output(t_command *command, int i)
{
	int	fd;

	printf("Output file :%s\n", command->fd[i].str);
	fd = open(command->fd[i].str, O_CREAT | O_RDWR | O_TRUNC, 0777);
	close(fd);
}

int	open_input(t_command *command,  int i)
{
	int	fd;

	printf("Input file :%s\n", command->fd[i].str);
	fd = open(command->fd[i].str, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (0);
}

int	open_last(t_command *command, int i)
{
	if (command->fd[i].token == 2)
		open_input(command, i);
	else if ((command->fd[i].token == 3))
		open_output(command, i);
	else if (command->fd[i].token == 4)
	{
		open_append(command, i);
		command->append_last = 1;
	}
	else if (command->fd[i].token == 1)
	{
		command->fd[i].heredoc_last = 1;
		heredoc_tmp_fd(command, i);
	}
	return (0);
}

int	open_fd(t_command *command)
{
	int	i;

	i = 0;
	command->append_last = 0;
	if (command->no_fd == 1)
		return (0);
	while (command->fd[i].last != 1)
	{
		command->fd[i].heredoc_last = 1;
		if (command->fd[i].token == 2)
			open_input(command, i);
		else if ((command->fd[i].token == 3))
			open_output(command, i);
		else if (command->fd[i].token == 4)
			open_append(command, i);
		else if (command->fd[i].token == 1)
			heredoc_tmp_fd(command, i);
		i++;
	}
	open_last(command, i);
	return (0);
}
