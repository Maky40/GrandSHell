/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_built_in_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:50:43 by xav               #+#    #+#             */
/*   Updated: 2024/03/30 10:55:13 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	single_process(char *cmd)
{
	int ret;

	ret = 1;
	if (check_command(cmd, "unset") == 0)
		ret = 0;
	else if (check_command(cmd, "cd") == 0)
		ret = 0;
	else if (check_command(cmd, "exit") == 0)
		ret = 0;
	else if (check_command(cmd, "export") == 0)
		ret = 0;
	return (ret);
}

void	built_in_execute(t_table *tab_cmds, t_data *data, t_env **env, int i)
{
	if (check_command(tab_cmds->commands[i].command, "echo") == 0)
		builtin_echo(&tab_cmds->commands[i], data);
	else if (check_command(tab_cmds->commands[i].command, "unset") == 0)
		do_unset(env, &tab_cmds->commands[i], data);
	else if (check_command(tab_cmds->commands[i].command, "cd") == 0)
		builtin_cd(&tab_cmds->commands[i], data);
	else if (check_command(tab_cmds->commands[i].command, "exit") == 0)
		ft_exit(env, data, tab_cmds);
	else if (check_command(tab_cmds->commands[i].command, "pwd") == 0)
		builtin_pwd(&tab_cmds->commands[i], data);
	else if (check_command(tab_cmds->commands[i].command, "env") == 0)
		printf("env\n");
	else if (check_command(tab_cmds->commands[i].command, "export") == 0)
		do_export(&tab_cmds->commands[i], data, env);
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
//	else if (check_command(cmd, "./minishell") == 0)
//		ret = 0;
	return (ret);
}
