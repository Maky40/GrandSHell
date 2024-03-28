/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:21:55 by mnie              #+#    #+#             */
/*   Updated: 2024/03/27 16:02:03 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	create_variable(t_env *env, char *str, int j)
{
	int		len;
	char	**new_tab;
	int		i;

	i = 0;
	len = 0;
	while (env -> tab[len])
		len++;
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (j == -1)
		j = len;
	while (i < j)
	{
		new_tab[i] = ft_strdup(env -> tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	while (i + 1 < len + 1)
	{
		new_tab[i + 1] = ft_strdup(env -> tab[i]);
		i++;
	}
	new_tab[i + 1] = '\0';
	free_dup_env(env -> tab);
	env -> tab = new_tab;
}
void	add_tab_plus_equal(t_env *env, char *str)
{
	char	*str_search;
	char	*str_without_plus;
	char	*new_str;
	int		pos;

	if (ft_strncmp(str, "_=", 2) == 0)
	{
		ft_printf("You can't modified _\n");
		return ;
	}
	str_search = variable_without_plus_equal(str);
	str_without_plus = variable_without_plus(str);
	if (search_variable(env -> tab, str_search) == -1)
		create_variable(env, str_without_plus, -1);
	else
	{
		pos = search_variable(env -> tab, str_search);
		new_str = add_variable(env -> tab, str_without_plus, pos);
		find_and_remove(env -> tab, str_search);
		create_variable(env, new_str, pos);
		free(new_str);
	}
	free(str_search);
	free(str_without_plus);
}

void	add_tab_equal(t_env *env, char *str)
{
	char	*str_search;
	int		pos;

	if (ft_strncmp(str, "_=", 2) == 0)
	{
		ft_printf("You can't modified _\n");
		return ;
	}
	str_search = variable_without_equal(str);
	if (search_variable(env -> tab, str_search) == -1)
		create_variable(env, str, -1);
	else
	{
		pos = search_variable(env -> tab, str_search);
		find_and_remove(env -> tab, str_search);
		create_variable(env, str, pos);
	}
	free(str_search);
}

void	add_tab(t_env *env, char *str)
{
	if (search_variable(env -> tab, str) != -1)
		return ;
	else
		create_variable(env, str, -1);
}

void	do_export(t_command *cmd, t_data *data, t_env **env)
{
	int		i;
	t_env	*node;

	node = last_env(env);
	i = 0;
	if (cmd -> arguments[i + 1] == NULL)
		export_simple(node -> tab);
	while (cmd -> arguments[++i])
	{
		if (ft_error_export(cmd -> arguments[i], data) == 1)
			return ;
		if (find_equal(cmd -> arguments[i]) == 0)
			add_tab(node, cmd -> arguments[i]);
		else if (before_equal(cmd -> arguments[i]) != '-' 	&& \
		before_equal(cmd -> arguments[i]) != '+')
			add_tab_equal(node, cmd -> arguments[i]);
		else if (before_equal(cmd -> arguments[i]) == '-')
			ft_error_export2("ERROR", data);
		else
			add_tab_plus_equal(node, cmd -> arguments[i]);
	}
	free_dup_env(data -> env);
	data -> env = dup_env(node -> tab);
	if (data -> exit_status != 1)
		data -> exit_status = 0;
}
