/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 09:52:55 by xav               #+#    #+#             */
/*   Updated: 2024/03/25 10:58:03 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo_quotes(t_command *cmd, int i)
{
	int ret;

	ret = 0;
	if (ft_strncmp(cmd->arguments[i], "\"\"", 3) == 0 
		|| ft_strncmp(cmd->arguments[i], "\'\'", 3) == 0)
	{
		if (cmd->arguments[i + 1] == NULL)
			ret = 1;
		else
			printf(" ");
		}
		else
			ft_printf("%s", cmd->arguments[i]);
	return (ret);
}

void print_end(int option, t_data *data)
{
	if (option == 0)
		ft_printf("\n");
	data->exit_status = 0;
}


void	builtin_echo(t_command *cmd, t_data *data)
{
	int i;
	int option;

	i = 1;
	option = 0;
	while (cmd->arguments[i])
	{
		if (ft_strncmp(cmd->arguments[1], "-n", 3) == 0)
		{
			option = 1;
			if (cmd->arguments[i + 1] != NULL)
				i++;
			else
				break;
		}
		if (echo_quotes(cmd, i) == 1)
			break;
		if (cmd->arguments[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	print_end(option, data);
}
