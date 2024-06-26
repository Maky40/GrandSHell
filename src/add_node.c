/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:42:13 by mnie              #+#    #+#             */
/*   Updated: 2024/04/04 10:50:45 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	identify_type_operators_2(t_data *data, int j, t_lexer *node)
{
	if (node->token != NUL)
		return ;
	if (data->line[j] == '>')
	{
		if (data->line[j + 1] == '>')
		{
			node->token = APPEND;
			j++;
			data->index_line = j;
		}
		else
			node->token = OUTPUT;
	}
	if (data->line[j] == '&')
	{
		if (data->line[j] == '&')
		{
			node->token = AND;
			j++;
			data->index_line = j;
		}
		else
			ft_printf("ERROR");
	}
}

void	identify_type_operators(t_data *data, int j, t_lexer *node)
{
	if (data->line[j] == '|')
		node->token = PIPE;
	if (data->line[j] == '<')
	{
		if (data->line[j + 1] == '<')
		{
			node->token = HEREDOC;
			j++;
			data->index_line = j;
		}
		else
			node->token = INPUT;
	}
}

void	identify_type_command(t_lexer *node)
{
	if (node->token != NUL)
		return ;
	if (node->prev == NULL || node->prev->token == PIPE)
	{
		node->token = COMMANDE;
		return ;
	}
	if (node->prev != NULL && (node->prev->token == COMMANDE
			|| node->prev->token == ARG || node->prev->token == FD))
		node->token = ARG;
	if (node->prev != NULL && (node->prev->token == HEREDOC
			|| node->prev->token == INPUT || node->prev->token == OUTPUT
			|| node->prev->token == APPEND))
		node->token = FD;
}

void	add_node(t_data *data, int i, int j, t_lexer **lexer)
{
	t_lexer	*node;
	int		k;

	k = 0;
	node = malloc(sizeof(t_lexer));
	if (!node)
		return ;
	node->token = NUL;
	node->str = malloc(sizeof(char) * (j - i + 2));
	while (k <= j - i)
	{
		node->str[k] = data->line[i + k];
		k++;
	}
	node->str[k] = '\0';
	add_node_to_lexer(lexer, node);
	identify_type_operators(data, j, node);
	identify_type_operators_2(data, j, node);
	identify_type_command(node);
	j = data->index_line;
}
