/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:42:17 by xav               #+#    #+#             */
/*   Updated: 2024/04/04 10:54:20 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	maj_old_pwd(t_data *data, int pos_pwd)
{
	char	*oldpwd;
	int		pos;

	oldpwd = malloc(sizeof(char) * 7);
	oldpwd[0] = 'O';
	oldpwd[1] = 'L';
	oldpwd[2] = 'D';
	oldpwd[3] = 'P';
	oldpwd[4] = 'W';
	oldpwd[5] = 'D';
	oldpwd[6] = '\0';
	pos = search_variable(data -> env, oldpwd);
	if (pos > -1)
		find_and_remove(data -> env, oldpwd);
	if (pos_pwd == -1)
		create_variable(data, oldpwd, pos);
	else
	{
		free(oldpwd);
		oldpwd = new_oldpwd(data -> env, pos_pwd);
		create_variable(data, oldpwd, pos);
	}
	free(oldpwd);
}

void	maj_export_pwd(t_data *data)
{
	char	*cwd;
	int		pos;
	char	*pwd;

	pwd = malloc(sizeof(char) * 4);
	pwd[0] = 'P';
	pwd[1] = 'W';
	pwd[2] = 'D';
	pwd[3] = '\0';
	cwd = getcwd(NULL, 0);
	pos = search_variable(data -> env, pwd);
	maj_old_pwd(data, pos);
	if (pos > -1)
		find_and_remove(data -> env, pwd);
	pwd = new_pwd(pwd, cwd);
	create_variable(data, pwd, pos);
	free(pwd);
}

void	go_home(t_command *cmd, t_data *data)
{
	if (chdir(get_env_value(data->env, "HOME")) != 0)
	{
		data->exit_status = 1;
		ft_printf("cd: HOME not set %s\n", cmd->arguments[1]);
		return ;
	}
	else
	{
		data->exit_status = 0;
		return ;
	}
}

void	builtin_cd(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->arguments[i])
		i++;
	if (i > 2)
	{
		data->exit_status = 1;
		write(2, "cd: too many arguments\n", 23);
		return ;
	}
	if (!cmd->arguments[1] || ft_strncmp(cmd->arguments[1], "~", 2) == 0)
		go_home(cmd, data);
	else
	{
		if (chdir(cmd->arguments[1]) != 0)
		{
			data->exit_status = 1;
			ft_printf("cd: no such file or directory: %s\n", cmd->arguments[1]);
			return ;
		}
		else
			data->exit_status = 0;
	}
	maj_export_pwd(data);
}
