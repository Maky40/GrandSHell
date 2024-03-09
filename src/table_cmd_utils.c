/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:11:11 by mnie              #+#    #+#             */
/*   Updated: 2024/03/09 09:53:21 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_last_fd(t_fd *fd, int j, int len)
{
	int	token;

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

int	len_fd(t_fd *fd)
{
	int	i;

	i = 0;
	while (fd[i].last != 1)
		i++;
	return (i);
}

t_fd	*malloc_fd(t_lexer *lst)
{
	t_lexer *lst2;
	int		i;
	t_fd	*fd;

	lst2 = lst;
	i = 0;
	while (lst2 && lst2 -> token == INPUT && lst2 -> token == OUTPUT \
	&& lst2 -> token == FD)
	{
		if (lst2 -> token == FD)
			i++;
		lst2 = lst2 -> next;
	}
	fd = malloc(sizeof(t_fd) * i);
	return (fd);
}
