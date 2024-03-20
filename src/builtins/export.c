/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:48:47 by mnie              #+#    #+#             */
/*   Updated: 2024/03/20 11:41:35 by mnie             ###   ########.fr       */
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

void	do_export(t_command *cmd, t_data *data, t_env **env)
{
	int	i;
	int	j;

	i = 0;
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
		if (ft_strchr(cmd -> arguments[i], '=') == 1)
			ft_printf("au moins un egal");
		else if (search_variable(last_env(env), cmd -> arguments[i]) == 0)
			create_variable(env, cmd -> arguments);
		i++;
	}
}