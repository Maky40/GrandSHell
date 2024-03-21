/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:50:43 by xav               #+#    #+#             */
/*   Updated: 2024/03/21 14:52:38 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	built_in_execute(t_command *cmd, t_data *data, t_env **env)
{
	(void)data;
	if (check_command(cmd->command, "echo") == 0)
		do_export(cmd, data, env);
	else if (check_command(cmd->command, "unset") == 0)
		printf("unset\n");
	else if (check_command(cmd->command, "cd") == 0)
		printf("cd\n");
	else if (check_command(cmd->command, "exit") == 0)
		printf("exit\n");
	else if (check_command(cmd->command, "pwd") == 0)
		printf("pwd\n");
	else if (check_command(cmd->command, "env") == 0)
		printf("env\n");
	else if (check_command(cmd->command, "export") == 0)
		do_export(cmd, data, env);
}

int check_command(char *str, char *cmd)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		if (str[i] != cmd[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	int ret;

	ret = 1;
	if (check_command(cmd, "echo") == 0)
		ret = 0;
	else if (check_command(cmd, "unset") == 0)
		ret = 0;
	else if (check_command(cmd, "cd") == 0)
		ret = 0;
	else if (check_command(cmd, "exit") == 0)
		ret = 0;
	else if (check_command(cmd, "pwd") == 0)
		ret = 0;
	else if (check_command(cmd, "env") == 0)
		ret = 0;
	else if (check_command(cmd, "export") == 0)
		ret = 0;
	return (ret);
}
/*
void last_command(t_table *tab_cmds, t_data *data, int i)
{
	pid_t	pid;
	int status;
	pid = fork();
	if (pid == 0)
	{
		if (tab_cmds->commands[i].input_file != NULL)
		{
			tab_cmds->commands[i].in_fd = open(tab_cmds->commands[i].input_file, O_RDONLY);
			dup2(tab_cmds->commands[i].in_fd, STDIN_FILENO);
		}
		if (tab_cmds->commands[i].output_file != NULL)
		{
			tab_cmds->commands[i].out_fd = exec_open_output(tab_cmds,i);
			dup2(tab_cmds->commands[i].out_fd, STDOUT_FILENO);
		}
		start_execute(data, tab_cmds, i);
	}
	else
		waitpid(pid, &status, 0);
}
*/