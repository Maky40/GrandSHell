/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:48:21 by xav               #+#    #+#             */
/*   Updated: 2024/04/03 14:04:46 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_double_quotes(t_data *data, int *j, int i, t_lexer **lexer)
{
	(*j)++;
	while (data->line[*j] && data->line[*j] != '"')
		(*j)++;
	if (search_operators(data->line[*j + 1]) == 1)
	{
		add_node(data, i, *j, lexer);
		(*j)++;
		data->index_line = *j;
		i = *j;
	}
}

void	process_single_quotes(t_data *data, int *j, int i, t_lexer **lexer)
{
	(*j)++;
	while (data->line[*j] && data->line[*j] != 39)
		(*j)++;
	if (search_operators(data->line[*j + 1]) == 1)
	{
		add_node(data, i, *j, lexer);
		(*j)++;
		data->index_line = *j;
		i = *j;
	}
}
