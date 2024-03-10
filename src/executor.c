/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:18:42 by xav               #+#    #+#             */
/*   Updated: 2024/03/09 12:41:16 by mnie             ###   ########.fr       */
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
	if (check_command(cmd, "echo"))
		echo();
	else if (check_command(cmd, "unset"))
		unset();
	else if (check_command(cmd, "cd"))
		cd();
	else if (check_command(cmd, "exit"))
		ft_exit();
	else if (check_command(cmd, "pwd"))
		pwd();
	else if (check_command(cmd, "env"))
		env();
	else if (check_command(cmd, "export"))
		export();
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

	while (i < tab_cmds->num_commands)
	{
		if (is_builtin(tab_cmds->commands[i].command) == 0)
			built_in_execute(&tab_cmds->commands[i], data);
		else
			execute(&tab_cmds->commands[i], data);
	}
}
