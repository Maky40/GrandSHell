/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 09:52:55 by xav               #+#    #+#             */
/*   Updated: 2024/04/05 12:35:36 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_option(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd->arguments[1][i])
		return (1);
	while (cmd->arguments[1][i])
	{
		if (cmd->arguments[1][i] == '-')
			i++;
		else
			return (1);
		while (cmd->arguments[1][i] == 'n' && cmd->arguments[1][i])
		{
			if (cmd->arguments[1][i] == 'n')
				i++;
			else
				return (1);
		}
	}
	return (0);
}

int	skip_option(t_command *cmd, int i)
{
	int	j;

	while (cmd->arguments[i])
	{
		j = 0;
		if (cmd->arguments[i][j] == '-')
			j++;
		else
			break ;
		while (cmd->arguments[i][j])
		{
			if (cmd->arguments[i][j] == 'n' && cmd->arguments[i][j])
				j++;
			else
				break ;
		}
		i++;
	}
	return (i);
}

int	echo_quotes(t_command *cmd, int i)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd->arguments[i], "\"\"", 3) == 0
		|| ft_strncmp(cmd->arguments[i], "\'\'", 3) == 0)
	{
		if (cmd->arguments[i + 1] == NULL)
			ret = 1;
	}
	else
		ft_printf("%s", cmd->arguments[i]);
	return (ret);
}

void	builtin_echo(t_command *cmd, t_data *data)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (cmd->arguments[i])
	{
		if (i == 1 && check_option(cmd) == 0 && cmd->arguments[i] != NULL)
		{
			option = 1;
			i = skip_option(cmd, i);
			if (cmd->arguments[i] == NULL)
				break ;
		}
		if (echo_quotes(cmd, i) == 1)
			break ;
		if (cmd->arguments[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (option == 0)
		ft_printf("\n");
	data->exit_status = 0;
}
