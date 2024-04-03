/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:41:36 by mnie              #+#    #+#             */
/*   Updated: 2024/04/03 10:49:21 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**remove_variable(char **env, int j)
{
	int	len;
	int	k;
	
	len = 0; 
	while (env[len])
		len++;
	free(env[j]);
	k = j;
	while (k < len -1)
	{
		env[k] = env[k + 1];
		k++;
	}
	env[len - 1] = NULL;
	return (env);
}
void	find_and_remove(char **env, char *arguments)
{
	int	j;

	j = 0;
	while (env[j])
	{
		if (ft_strncmp(arguments, env[j], ft_strlen(arguments)) == 0 \
		&& arguments[0] != '_')
		{
			env = remove_variable(env, j);
			return ;
		}
		j++;
	}
}

void	do_unset(t_command *cmd, t_data *data)
{
	int	i;
	
	i = 1;
	while (cmd -> arguments[i])
	{
		if (search_variable(data->env, cmd->arguments[i]))
			find_and_remove(data->env, cmd->arguments[i]);
		i++;
	}
	data->exit_status = 0;
}