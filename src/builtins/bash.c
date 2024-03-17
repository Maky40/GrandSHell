/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:07:35 by mnie              #+#    #+#             */
/*   Updated: 2024/03/17 15:52:43 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bash(t_env **env)
{
	t_env	*lst;
	t_env	*new;

	lst = *env;
	while (lst -> next)
		lst = lst -> next;
	new = malloc(sizeof(t_env));
	new -> modified_env = dup_env(lst -> modified_env);
	new -> shel_lvl = lst -> shel_lvl + 1;
	new -> vars_add = dup_env(lst -> vars_add);
	new -> next = NULL;
	lst -> next = new;
}