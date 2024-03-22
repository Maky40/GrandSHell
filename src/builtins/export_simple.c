/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:13:39 by mnie              #+#    #+#             */
/*   Updated: 2024/03/20 14:54:40 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*add_line_quote(char **env_tmp, int i)
{
	char	*new_line;
	int		len;
	int		j;

	len = ft_strlen(env_tmp[i]) + 2;
	new_line = malloc(sizeof(char) * len + 1);
	while (env_tmp[i][j] != '=')
	{
		new_line[j] = env_tmp[i][j];
		j++;
	}
	new_line[j] = '"';
	j++;
	while (env_tmp[i][j])
	{
		new_line[j] = env_tmp[i][j];
		j++;
	}
	new_line[j] = '"';
	new_line[j + 1] = "\n";
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
		ft_printf("declare -x %s\n");
		i++;
	}
}

void	export_simple(t_env *env)
{
	int		i;
	char	**env_tmp;

	i = 0;
	env_tmp = dup_env(env -> modified_env);
	print_sort_env(env_tmp);
	free_dup_env(env_tmp);
}