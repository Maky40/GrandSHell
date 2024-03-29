/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:28:18 by mnie              #+#    #+#             */
/*   Updated: 2024/03/26 16:45:40 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_t_env(t_env *env)
{
	if (env == NULL)
		return;
	free_dup_env(env->tab);
	free(env);
}

void	free_builtin_process(t_table *tab_cmds, t_data *data, t_env **env)
{
	int	i;

	i = 0;
	free_dup_env(data->env);
	free_t_env(*env);
	if (data->quote_space)
		free(data->quote_space);
	if (!tab_cmds)
		return ;
	while (i < tab_cmds -> num_commands)
	{
		free_commands(tab_cmds -> commands, i);
		i++;
	}
	free(tab_cmds->commands);
	free (tab_cmds);
	tab_cmds = NULL;
}

void	free_data_end(t_data *data)
{
	free(data -> line);
	free(data -> quote_space);
	free_dup_env(data -> env);
	free (data);
}

int	verify_line(t_lexer **lexer)
{
	t_lexer	*lst;

	lst = *lexer;
	while (lst)
	{
		if (lst -> token == INPUT)
		{
			if (lst -> next != NULL && lst -> next -> token != FD)
				return (1);
		}
		lst = lst -> next;
	}
	return (0);
}

void	free_all(t_data *data, t_lexer **lexer)
{
	free_lexer(lexer);
	free_data_end(data);
}