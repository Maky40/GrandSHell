/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:48:47 by mnie              #+#    #+#             */
/*   Updated: 2024/03/16 09:20:27 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_variable(t_env *env, char *variable)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (env -> vars_add[i])
		i++;
	new_tab = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (env -> vars_add[i])
	{
		new_tab[i] = ft_strdup(env -> vars_add[i]);
		i++;
	}
	new_tab[i] = ft_strdup(variable);
	new_tab[i] = NULL;
	free_dup_env(env -> vars_add);
	env -> vars_add = new_tab;
}

void	export_variable(t_env *env, char *variable)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (env -> modified_env[i])
	{
		if (ft_strncmp(variable, env -> modified_env[i], ft_strlen(variable)) == 0 \
			&& env -> modified_env[i][ft_strlen(variable)] == '=')
			{
				ft_printf("%s\n", env -> modified_env[i]);
				k = 1;
			}
		i++;
	}
	i = 0;
	while (env -> vars_add[i])
	{
		if (ft_strncmp(variable, env -> vars_add[i], ft_strlen(variable)) == 0 \
			&& env -> vars_add[i][ft_strlen(variable)] == '=')
			{
				ft_printf("%s\n", env -> vars_add[i]);
				k = 1;
			}
		i++;
	}
	if (k == 0)
		create_variable(env, variable);
}

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
	env_tmp = dup_env(env -> vars_add);
	if (env_tmp[0])
	{
		print_sort_env(env_tmp);
		free_dup_env(env_tmp);
	}
}

void	do_export(t_command *cmd, t_data *data, t_env **env)
{
	int	i;
	int	j;

	i = 0;
	if (cmd -> arguments[i] == NULL)
		export_simple(last_env(env));
	while (cmd -> arguments[i])
	{
		if (check_command(cmd->arguments[i], "-n"))
			ft_printf("-n");
		else if (check_command(cmd->arguments[i], "-p"))
			ft_printf("-p");
		else if (ft_strchr(cmd -> arguments[i], '=') == 1)
			ft_printf("au moins un egal");
		else
			ft_printf("export variable");
		i++;
	}
}