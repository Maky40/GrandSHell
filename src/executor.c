/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:18:42 by xav               #+#    #+#             */
/*   Updated: 2024/04/05 12:22:22 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	file_redirect(t_table *tab_cmds, int i)
{
	if (tab_cmds->commands[i].input_file != NULL)
	{
		tab_cmds->commands[i].in_fd = open(tab_cmds->commands[i].input_file,
				O_RDONLY);
		dup2(tab_cmds->commands[i].in_fd, STDIN_FILENO);
	}
	if (tab_cmds->commands[i].output_file != NULL)
	{
		tab_cmds->commands[i].out_fd = exec_open_output(tab_cmds, i);
		dup2(tab_cmds->commands[i].out_fd, STDOUT_FILENO);
	}
}

void	close_and_update_pipes(int i, t_data *data)
{
	if (i > 0)
	{
		close(data->prev_pipe[0]);
		close(data->prev_pipe[1]);
	}
	data->prev_pipe[0] = data->curr_pipe[0];
	data->prev_pipe[1] = data->curr_pipe[1];
}

void	redirect_pipes(int i, int num_commands, t_data *data)
{
	if (i > 0)
	{
		close(data->prev_pipe[1]);
		dup2(data->prev_pipe[0], STDIN_FILENO);
		close(data->prev_pipe[0]);
	}
	if (i < num_commands - 1)
	{
		close(data->curr_pipe[0]);
		dup2(data->curr_pipe[1], STDOUT_FILENO);
		close(data->curr_pipe[1]);
	}
}

void	execute_command(int i, t_table *tab_cmds, t_data *data)
{
	pid_t	pid;

	if (tab_cmds->commands[i].command == NULL)
		return ;
	tab_cmds->commands[i].builtin_process = 0;
	if (tab_cmds->num_commands == 1
		&& is_builtin_first(tab_cmds->commands[i].command) == 0)
	{
		redirect_pipes(i, tab_cmds->num_commands, data);
		file_redirect(tab_cmds, i);
		start_execute(data, tab_cmds, i);
	}
	else
	{
		tab_cmds->commands[i].builtin_process = 1;
		pid = fork();
		if (pid == 0)
		{
			redirect_pipes(i, tab_cmds->num_commands, data);
			file_redirect(tab_cmds, i);
			start_execute(data, tab_cmds, i);
			exit(EXIT_SUCCESS);
		}
	}
}

void	executor(t_table *tab_cmds, t_data *data)
{
	int	i;
	int	status;

	status = 0;
	pipe(data->prev_pipe);
	i = -1;
	while (++i < tab_cmds->num_commands)
	{
		if (i < tab_cmds->num_commands - 1)
			pipe(data->curr_pipe);
		if (open_fd(&tab_cmds->commands[i], data) == 0)
			execute_command(i, tab_cmds, data);
		close_and_update_pipes(i, data);
	}
	i = -1;
	while (++i < tab_cmds->num_commands)
	{
		wait(&status);
		if (WIFEXITED(status)
			&& !(is_builtin(tab_cmds->commands[i].command) == 0))
			data->exit_status = WEXITSTATUS(status);
	}
}
