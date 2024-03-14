/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:48:47 by mnie              #+#    #+#             */
/*   Updated: 2024/03/14 14:38:31 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_simple(t_command *cmd, t_data *data)
{
	int		i;
	char	**env_tmp;
	char	*swap;

	i = 0;
	env_tmp = dup_env(data -> env);
	while (env_tmp[i + 1])
	{
		if (ft_strncmp(env_tmp[i], env_tmp[i + 1], ft_strlen(env_tmp[i])) > 0)
		{
			swap = env_tmp[i + 1];
			env_tmp[i + 1] = env_tmp[i];
			env_tmp[i] = swap;
			i = -1;
		}
		i++;
	}
	free_dup_env(env_tmp);
}

void	do_export(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (cmd -> arguments[i] == NULL)
		export_simple(cmd, data);
	while (cmd -> arguments[i])
	{
		if (cmd -> arguments[i])
		i++;
	}
}