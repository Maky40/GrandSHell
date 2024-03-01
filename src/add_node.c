/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:42:13 by mnie              #+#    #+#             */
/*   Updated: 2024/02/29 15:54:34 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*lstlast(t_lexer *lst)
{
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	add_node_to_lexer(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		new -> prev = NULL;
		new -> next = NULL;
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last -> next = new;
	new -> prev = last;
}

void	identify_type_operators_2(t_data *data, int i, int j, t_lexer *node)
{
	if (data -> line[j] == '>')
	{
		if (data -> line[j] == '>')
		{
			node -> token = APPEND;
			j++;
		}
		else
			node -> token = PIPE;
	}
	if (data -> line[j] == '&')
	{
		if (data -> line[j] == '&')
		{
			node -> token = AND;
			j++;
		}
		else
			ft_printf("ERROR");
	}
}
void	identify_type_operators(t_data *data, int i, int j, t_lexer *node)
{
	if (data -> line[j] == '|')
	{
		if (data -> line[j] == '|')
		{
			node -> token = OR;
			j++;
		}
		else
			node -> token = PIPE;
	}
	if (data -> line[j] == '<')
	{
		if (data -> line[j] == '<')
		{
			node -> token = HEREDOC;
			j++;
		}
		else
			node -> token = INPUT;
	}

}

void	add_node(t_data *data, int i, int j, t_lexer **lexer)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	add_node_to_lexer(lexer, node);
	identify_type_operators(data, i, j, node);
}
