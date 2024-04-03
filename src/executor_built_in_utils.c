/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_built_in_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:50:43 by xav               #+#    #+#             */
/*   Updated: 2024/04/03 15:03:31 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_open_output(t_table *tab_cmds, int i)
{
	if (tab_cmds->commands->append_last == 1)
	{
		return (open(tab_cmds->commands[i].output_file,
				O_CREAT | O_RDWR | O_APPEND, 0777));
	}
	else
	{
		return (open(tab_cmds->commands[i].output_file,
				O_CREAT | O_RDWR | O_TRUNC, 0777));
	}
}

void	built_in_execute(t_table *tab_cmds, t_data *data, int i)
{
	if (ft_strncmp(tab_cmds->commands[i].command, "echo", 5) == 0)
		builtin_echo(&tab_cmds->commands[i], data);
	else if (ft_strncmp(tab_cmds->commands[i].command, "unset", 6) == 0)
		do_unset(&tab_cmds->commands[i], data);
	else if (ft_strncmp(tab_cmds->commands[i].command, "cd", 3) == 0)
		builtin_cd(&tab_cmds->commands[i], data);
	else if (ft_strncmp(tab_cmds->commands[i].command, "exit", 5) == 0)
	{
		data->exit = 1;
		ft_exit(data, tab_cmds);
	}
	else if (ft_strncmp(tab_cmds->commands[i].command, "pwd", 4) == 0)
		builtin_pwd(&tab_cmds->commands[i], data);
	else if (ft_strncmp(tab_cmds->commands[i].command, "env", 3) == 0)
		print_env(&tab_cmds->commands[i], data);
	else if (ft_strncmp(tab_cmds->commands[i].command, "export", 7) == 0)
		do_export(&tab_cmds->commands[i], data);
}

int	is_builtin(char *cmd)
{
	int	ret;

	ret = 1;
	if (cmd == NULL)
		return (ret);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ret = 0;
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ret = 0;
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ret = 0;
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ret = 0;
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ret = 0;
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ret = 0;
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ret = 0;
	return (ret);
}
