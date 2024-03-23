/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:48:47 by mnie              #+#    #+#             */
/*   Updated: 2024/03/23 13:14:41 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_variable(t_env **env, char *variable)
{
	int		i;
	char	**new_tab;
	t_env	*env_tmp;

	env_tmp = *env;
	i = 0;
	while (env_tmp -> next)
		env_tmp = env_tmp -> next;
	while (env_tmp -> vars_add[i])
		i++;
	new_tab = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (env_tmp -> vars_add[i])
	{
		new_tab[i] = ft_strdup(env_tmp -> vars_add[i]);
		i++;
	}
	new_tab[i] = ft_strdup(variable);
	new_tab[i  + 1] = NULL;
	i = 0;
	free_dup_env(env_tmp -> vars_add);
	env_tmp -> vars_add = new_tab;
}

void	do_export(t_command *cmd, t_data *data, t_env **env)
{
	int	i;
	t_env 	*lst;

	i = 1;
	ft_printf("cmd -> arguments = %s\n", cmd -> arguments[i]);
	if (cmd -> arguments[i] == NULL)
		export_simple(env);
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
			create_variable(env, cmd -> arguments[i]);
		free (data -> env);
		data -> env = dup_env(last_env(env));
		i++;
	}
	lst = *env;
	while (lst -> next)
		lst = lst -> next;
	ft_printf("fin de do_export : %s\n", lst -> vars_add[0]);
}