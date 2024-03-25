/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:48:47 by mnie              #+#    #+#             */
/*   Updated: 2024/03/25 11:22:44 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_modified(t_env *env, char *str)
{
	int	i;
	char **new_tab;

	i = 0;
	while (env -> modified_env[i])
		i++;
	new_tab = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (env -> modified_env[i])
	{
		new_tab[i] = ft_strdup(env -> modified_env[i]);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	new_tab[i + 1] = '\0';
	free_dup_env(env -> modified_env);
	env -> modified_env = new_tab;
}

void	maj_tabs(t_env *env)
{
	int	i;

	i = 0;
	while (env -> vars_add[i])
	{
		if (find_equal(env -> vars_add[i]) == 1)
		{
			delete_after_equal(env -> vars_add, i);
			add_modified(env, env -> vars_add[i]);
			do_unset2(env, env -> vars_add[i], 2);
			i = -1;
		}
		i++;
	}
	i = 0;
	while (env -> modified_env[i])
	{
		ft_printf("%s\n");
		i++;
	}
}
void	create_variable(t_env **lst, char *variable)
{
	int		i;
	char	**new_tab;
	t_env	*env;

	env = *lst;
	while (env -> next)
		env = env -> next;
	i = 0;
	while (env -> vars_add[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env -> vars_add[i])
	{
		new_tab[i] = ft_strdup(env -> vars_add[i]);
		i++;
	}
	new_tab[i] = ft_strdup(variable);
	new_tab[i  + 1] = NULL;
	free_dup_env(env -> vars_add);
	env -> vars_add = new_tab;
	ft_printf("FIN FCT\n");
	i = 0;
	while (env -> vars_add[i])
	{
		ft_printf("%s\n", env -> vars_add[i]);
		i++;
	}
	ft_printf("FIN WHILE \n");
	// free_dup_env(new_tab);
}

void	do_export(t_command *cmd, t_data *data, t_env **env)
{
	int	i;
	t_env *lst;

	lst = *env;
	while (lst -> next)
		lst = lst -> next;
	i = 0;
	while (lst -> vars_add[i])
	{
		ft_printf("%s\n", lst -> vars_add);
		i++;
	}
	i = 1;
	ft_printf("cmd -> arguments = %s\n", cmd -> arguments[i]);
	if (cmd -> arguments[i] == NULL)
		export_simple(env);
	while (cmd -> arguments[i])
	{
		if (ft_error_export(cmd -> arguments[i])==1)
			i++;
		else if (find_equal(cmd -> arguments[i]) == 1)
		{
			export_with_equal(last_env(env), cmd -> arguments[i]);
			maj_tabs(last_env(env));
		}
		else if (search_variable(last_env(env), cmd -> arguments[i]) == 0)
		{
			ft_printf("je passe dans export sans =\n");
			create_variable(env, cmd -> arguments[i]);
		}
		free (data -> env);
		data -> env = dup_env(lst -> modified_env);
		i++;
	}
	ft_printf("------APRES LA BOUCLE--------\n");
	i = 0;
	while (lst -> vars_add[i])
	{
		ft_printf("%s\n", lst -> vars_add[i]);
		i++;
	}
}