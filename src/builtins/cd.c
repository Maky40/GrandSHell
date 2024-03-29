/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:42:17 by xav               #+#    #+#             */
/*   Updated: 2024/03/27 15:59:42 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	{
		go_home(cmd, data);
	}
	else
	{
		if (chdir(cmd->arguments[1]) != 0)
		{
			data->exit_status = 1;
			ft_printf("cd: no such file or directory: %s\n", cmd->arguments[1]);
		}
		else
			data->exit_status = 0;
	}
}
