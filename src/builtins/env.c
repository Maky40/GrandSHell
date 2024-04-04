/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:44:35 by xav               #+#    #+#             */
/*   Updated: 2024/04/03 19:44:13 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



void	print_env3(char *str, char *str_search)
{
	int		i;
	int		num;
	char	*new_str;

	i = 0;
	while ((str[i] < '0' || str[i] > '9') && str[i])
			i++;
	if (str[i] == '\0')
	{
		free(str_search);
		ft_printf("%s\n", str);
	}
	num = ft_atoi((str + i)) - 1;
	new_str = ft_itoa(num);
	new_str = ft_spe_strjoin(str_search, new_str);
	ft_printf("%s\n", new_str);
	free(new_str);
	free(str_search);
}


void	print_env2(char *str)
{
	char	*str_search;

	str_search = malloc(sizeof(char) * 7);
	str_search[0] = 'S';
	str_search[1] = 'H';
	str_search[2] = 'L';
	str_search[3] = 'V';
	str_search[4] = 'L';
	str_search[5] = '=';
	str_search[6] = '\0';
	if (ft_strncmp(str_search, str, ft_strlen(str_search)) == 0 && \
	ft_strlen(str) > 6 && ft_alldigit(str + 6) == 1)
	{
		print_env3(str, str_search);
		return ;
	}
	free(str_search);
	ft_printf("%s\n", str);
}

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
		print_env2(data -> env[i]);
		i++;
	}
	data->exit_status = 0;
}
