/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:03:53 by mnie              #+#    #+#             */
/*   Updated: 2024/02/27 14:09:34 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_dup_env(char **dup_env)
{
	int		i;

	i = 0;
	while (dup_env[i])
	{
		free(dup_env[i]);
		i++;
	}
	free(dup_env);
	dup_env = NULL;
	return ;
}

char 	**dup_env(char **envp)
{
	int		i;
	char	**env_dup;

	i = 0;
	while (envp[i])
		i++;
	env_dup = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		env_dup[i] = ft_strdup(envp[i]);
		i++;
	}
	env_dup[i] = NULL;
	return (env_dup);
}