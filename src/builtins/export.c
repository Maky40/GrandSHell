/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:21:55 by mnie              #+#    #+#             */
/*   Updated: 2024/04/04 14:20:21 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_variable(t_data *data, char *str, int j)
{
	int		len;
	char	**new_tab;
	int		i;

	i = 0;
	len = 0;
	while (data -> env[len])
		len++;
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (j == -1)
		j = len;
	while (i < j)
	{
		new_tab[i] = ft_strdup(data -> env[i]);
		i++;
	}
	new_tab[i] = add_str(str);
	while (i + 1 < len + 1)
	{
		new_tab[i + 1] = ft_strdup(data -> env[i]);
		i++;
	}
	new_tab[i + 1] = NULL;
	free_dup_env(data -> env);
	data -> env = new_tab;
}

void	add_tab_plus_equal(t_data *data, char *str)
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
	if (search_variable(data -> env, str_search) == -1)
		create_variable(data, str_without_plus, -1);
	else
	{
		pos = search_variable(data -> env, str_search);
		new_str = add_variable(data -> env, str_without_plus, pos);
		find_and_remove(data -> env, str_search);
		create_variable(data, new_str, pos);
		free(new_str);
	}
	free(str_search);
	free(str_without_plus);
}

void	add_tab_equal(t_data *data, char *str)
{
	char	*str_search;
	int		pos;

	if (ft_strncmp(str, "_=", 2) == 0)
	{
		ft_printf("You can't modified _\n");
		return ;
	}
	str_search = variable_without_equal(str);
	if (search_variable(data -> env, str_search) == -1)
		create_variable(data, str, -1);
	else
	{
		pos = search_variable(data -> env, str_search);
		find_and_remove(data -> env, str_search);
		create_variable(data, str, pos);
	}
	free(str_search);
}

void	add_tab(t_data *data, char *str)
{
	if (search_variable(data -> env, str) != -1)
		return ;
	else
		create_variable(data, str, -1);
}

void	do_export(t_command *cmd, t_data *data)
{
	int		i;

	i = 0;
	if (cmd -> arguments[i + 1] == NULL)
		export_simple(data -> env);
	while (cmd -> arguments[++i])
	{
		if (ft_error_export(cmd -> arguments[i]) == 1)
		{
			ft_error_export2("ERROR", data);
			return ;
		}
		if (find_equal(cmd -> arguments[i]) == 0)
			add_tab(data, cmd -> arguments[i]);
		else if (before_equal(cmd -> arguments[i]) != '-' && \
		before_equal(cmd -> arguments[i]) != '+')
			add_tab_equal(data, cmd -> arguments[i]);
		else if (before_equal(cmd -> arguments[i]) == '-')
			ft_error_export2("ERROR", data);
		else
			add_tab_plus_equal(data, cmd -> arguments[i]);
	}
	if (data -> exit_status != 1)
		data -> exit_status = 0;
}
