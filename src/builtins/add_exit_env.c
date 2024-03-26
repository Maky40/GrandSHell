/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:07:35 by mnie              #+#    #+#             */
/*   Updated: 2024/03/26 16:51:31 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit

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