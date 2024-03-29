/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_built_in_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:50:43 by xav               #+#    #+#             */
/*   Updated: 2024/03/26 16:41:58 by mnie             ###   ########.fr       */
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

void	built_in_execute(t_command *cmd, t_data *data, t_env **env)
{
	t_env *lst;

	(void)data;
	(void)env;

	if (check_command(cmd->command, "echo") == 0)
		builtin_echo(cmd, data);
	else if (check_command(cmd->command, "unset") == 0)
		printf("unset\n");
	else if (check_command(cmd->command, "cd") == 0)
		builtin_cd(cmd, data);
	else if (check_command(cmd->command, "exit") == 0)
		printf("exit\n");
	else if (check_command(cmd->command, "pwd") == 0)
		builtin_pwd(cmd, data);
	else if (check_command(cmd->command, "env") == 0)
		printf("env\n");
	else if (check_command(cmd->command, "export") == 0)
		do_export(cmd, data, env);
	lst = *env;
	while (lst -> next)
		lst = lst -> next;
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
