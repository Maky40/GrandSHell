/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:13:39 by mnie              #+#    #+#             */
/*   Updated: 2024/03/23 16:59:06 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**dup_env_var2(char **tab, char **modified, char **add)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (modified[i])
	{
		tab[j] = ft_strdup(modified[i]);
		j++;
		i++;
	}
	i = 0;
	while (add[i])
	{
		tab[j] = ft_strdup(add[i]);
		j++;
		i++;
	}
	tab[j] = '\0';
	return (tab);
}

char	**dup_env_var(t_env *env)
{
	int	i;
	int	j;
	char **tab;

	i = 0;
	j = 0;
	while (env -> modified_env[i])
	{
		j++;
		i++;
	}
	i = 0;
	while (env -> vars_add[i])
	{
		j++;
		i++;
	}
	tab = malloc(sizeof(char *) * (j + 1));
	tab = dup_env_var2(tab, env -> modified_env, env -> vars_add);
	return (tab);
}
char	*add_line_quote(char **env_tmp, int i)
{
	char	*new_line;
	int		len;
	int		j;

	j = 0;
	len = ft_strlen(env_tmp[i]) + 2;
	new_line = malloc(sizeof(char) * len + 1);
	while (env_tmp[i][j] != '=')
	{
		new_line[j] = env_tmp[i][j];
		j++;
	}
	new_line[j] = env_tmp[i][j];
	j++;
	new_line[j] = '"';
	while (env_tmp[i][j])
	{
		new_line[j + 1] = env_tmp[i][j];
		j++;
	}
	new_line[j + 1] = '"';
	new_line[j + 2] = '\0';
	free(env_tmp[i]);
	return(new_line);
}

void	print_sort_env(char **env_tmp)
{
	char	*swap;
	int		i;

	i = 0;
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
	i = 0;
	while (env_tmp[i])
	{
		env_tmp[i] = add_line_quote(env_tmp, i);
		ft_printf("declare -x %s\n", env_tmp[i]);
		i++;
	}
}

void	export_simple(t_env **env)
{
	char	**env2;
	t_env	*env_tmp;

	env_tmp = *env;
	while (env_tmp -> next)
		env_tmp = env_tmp -> next;
	env2 = dup_env_var(env_tmp);
	print_sort_env(env2);
	free_dup_env(env2);
}