/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:41:36 by mnie              #+#    #+#             */
/*   Updated: 2024/03/26 16:50:34 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**remove_variable(char **env, int j)
{
	int		len;
	char	**new_env;

	len = 0;
	while (env[len])
		len++;
	new_env = malloc(sizeof(char *) * len);
	new_env[len - 1] = NULL;
	len = 0;
	while (len < j)
	{
		new_env[len] = ft_strdup(env[len]);
		len++;
	}
	j++;
	while (env[j])
	{
		new_env[len] = ft_strdup(env[j]);
		j++;
		len++;
	}
	free_dup_env(env);
	env = dup_env(new_env);
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

void	do_unset(t_env **env, t_command *cmd)
{
	int	i;
	t_env *lst;

	lst = last_env(env);
	i = 1;
	while (cmd -> arguments[i])
	{
		if (search_variable(lst -> tab, cmd -> arguments[i]))
			find_and_remove(lst -> tab, cmd -> arguments[i]);
		else
			ft_printf("ERROR for %s, variable not found\n", cmd -> arguments[i]);
		i++;
	}
}