/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:48:47 by mnie              #+#    #+#             */
/*   Updated: 2024/03/21 14:38:44 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_variable(char **env, char *variable)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (env)
		i++;
	new_tab = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (env[i])
	{
		new_tab[i] = ft_strdup(env[i]);
		i++;
	}
	new_tab[i] = ft_strdup(variable);
	new_tab[i] = NULL;
	free_dup_env(env);
	env = new_tab;
}

void	do_export(t_command *cmd, t_data *data, t_env **env)
{
	int	i;

	i = 0;
	ft_printf("je rentre\n");
	if (cmd -> arguments[i] == NULL)
		export_simple(last_env(env));
	while (cmd -> arguments[i])
	{
		if (ft_error_export(cmd -> arguments[i])==1)
			i++;
		// if (check_command(cmd->arguments[i], "-n"))
		// 	ft_printf("-n");
		// else if (check_command(cmd->arguments[i], "-p"))
		// 	ft_printf("-p");
		if (ft_strchr(cmd -> arguments[i], "=") == 1)
			export_with_equal(last_env(env), cmd -> arguments[i]);
		else if (search_variable(last_env(env), cmd -> arguments[i]) == 0)
			create_variable(last_env(env), cmd -> arguments[i]);
		free (data -> env);
		data -> env = dup_env(last_env(env));
		i++;
	}
}