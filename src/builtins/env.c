/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:44:35 by xav               #+#    #+#             */
/*   Updated: 2024/04/02 09:40:22 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(t_command *cmd, t_data *data)
{
	int i;

	i = 0; 
	while (cmd->arguments[i] && i < 2)
		i++;
	if (i > 2)
	{
		ft_printf("env: '%s': No such file or directory\n", cmd->arguments[i]);
		data->exit_status = 127;
		return ;
	}
	i = 0;
	while(data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	data->exit_status = 0;
}
