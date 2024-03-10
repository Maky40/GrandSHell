/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:11:11 by mnie              #+#    #+#             */
/*   Updated: 2024/03/10 20:44:15 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_last_fd(t_fd *fd, int j, int len)
{
	t_tokens	token;

	token = fd[j].token;
	j++;
	while (j < len)
	{
		if (token == fd[j].token)
			return (0);
		j++;
	}
	return (1);
}

void	nb_command(t_table *tab_cmds, t_lexer **lexer)
{
	int		i;
	t_lexer	*lst;

	i = 0;
	lst = *lexer;
	while(lst)
	{
		if (lst -> token == COMMANDE)
			i++;
		lst = lst -> next;
	}
	tab_cmds -> num_commands = i;
	return ;
}
