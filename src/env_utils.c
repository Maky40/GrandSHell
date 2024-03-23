/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:03:53 by mnie              #+#    #+#             */
/*   Updated: 2024/03/23 14:26:11 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**last_env(t_env **env)
{
	t_env	*lst;

	lst = *env;
	while (lst -> next)
		lst = lst -> next;
	return (lst -> modified_env);
}
void	env_init(t_env **env, char **envp)
{
	t_env	*env_tmp;

	// ft_printf("la\n");
	// ft_printf("la1\n");
	env = malloc(sizeof(t_env *));
	env_tmp = malloc(sizeof(t_env));
	env_tmp -> shel_lvl = 1;
	env_tmp -> modified_env = dup_env(envp);
	env_tmp -> next = NULL;
	env_tmp -> vars_add = malloc(sizeof(char*));
	env_tmp -> vars_add[0] = NULL;
	*env = env_tmp;
}

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


void	free_data(t_data *data)
{
	free(data -> line);
	free(data -> quote_space);
	free_dup_env(data -> env);
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
