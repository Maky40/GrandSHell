/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:07:35 by mnie              #+#    #+#             */
/*   Updated: 2024/04/05 09:37:52 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_cmd_exit(t_table *cmd)
{
	int	i;

	i = 0;
	while (i < cmd -> num_commands)
	{
		if (ft_strncmp(cmd->commands[i].command, "exit", 5) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	ft_error_while(char *str)
{
	int	i;
	int	line;

	i = 1;
	line = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '=')
			line = i;
		if ((str[i] == '-' || str[i] == '+') && (str[i + 1] != '=' || i > line))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_data *data, t_table *cmd)
{
	int	i;
	int	pos;

	i = 1;
	if (data->exit == 1)
	{
		pos = find_cmd_exit(cmd);
		while (cmd -> commands[pos].arguments[i])
			i++;
		if (pos == 0)
			ft_putstr("exit\n");
		if (i > 2)
			ft_putstr("bash : exit : too many arguments\n");
		if (i - 1 == 1
			&& ft_alldigit(cmd -> commands[pos].arguments[i - 1]) == 0)
			ft_putstr("bash : exit : numeric argument require\n");
		free_table_cmd(cmd);
	}
	else
		ft_putstr("exit\n");
	free_data_end(data);
	exit (0);
}
