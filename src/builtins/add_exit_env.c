/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:07:35 by mnie              #+#    #+#             */
/*   Updated: 2024/04/02 10:47:47 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_last_env(t_env **env)
{
	t_env	*node;

	node = last_env(env);
	free_dup_env(node -> tab);
	free (node);
	node = NULL;
}

void	ft_exit(t_env **env, t_data *data, t_table *cmd)
{
	t_env	*node;
	(void) cmd;
	node = last_env(env);
	/*
	if (cmd != NULL)
		free_table_cmd(cmd);
	*/
	if (node -> shel_lvl == 1)
	{
		free_data_end(data);
	}
	free_last_env(env);
	ft_putstr("exit\n");
	exit (0);
}

void	add_env(t_env **env)
{
	t_env	*lst;
	t_env	*new;

	lst = *env;
	while (lst -> next)
		lst = lst -> next;
	new = malloc(sizeof(t_env));
	new -> tab = dup_env(lst -> tab);
	new -> shel_lvl = lst -> shel_lvl + 1;
	new -> next = NULL;
	lst -> next = new;
}

void	env(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (find_equal(tab[i]) == 1)
			ft_printf("%s\n", tab[i]);
		i++;
	}
}