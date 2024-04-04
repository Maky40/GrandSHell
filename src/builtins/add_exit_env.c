/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:07:35 by mnie              #+#    #+#             */
/*   Updated: 2024/04/03 15:37:56 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	(void) cmd;
	if (data->exit == 1)
		free_table_cmd(cmd);
	free_data_end(data);
	ft_putstr("exit\n");
	exit (0);
}
