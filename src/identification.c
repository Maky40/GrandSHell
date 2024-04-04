/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:21:27 by mnie              #+#    #+#             */
/*   Updated: 2024/04/04 14:44:08 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*lst;
	t_lexer	*next_node;

	if (!lexer || !(*lexer))
		return ;
	lst = *lexer;
	while (lst)
	{
		next_node = lst->next;
		if (lst->str != NULL)
			free(lst->str);
		free(lst);
		lst = next_node;
	}
	*lexer = NULL;
}

void	str_operators(t_data *data, int j, int i, t_lexer **lexer)
{
	if (data -> line[j] == '"' || data -> line[j] == 39)
		j++;
	while (data->line[j] != '|' && data->line[j] != '>' && \
	data->line[j] != '<' && data->line[j] != '&' && data->line[j] && \
	data->line[j] != ' ' && data->line[j] != '"' && data->line[j] != 39 && \
	data -> line[j])
		j++;
	if (data -> line[j] == '"' || data -> line[j] == 39)
		str_quotes_operators(data, j, i, lexer);
	else
	{
		add_node(data, i, j - 1, lexer);
		i = j;
		data -> index_line = j;
		if (data -> line[j] == '\0')
			return ;
		if (data -> line[j] == '|' || data -> line[j] == '>' )
			add_node(data, i, j, lexer);
		if (data -> line[j] == '<' || data -> line[j] == '&')
			add_node(data, i, j, lexer);
		j = data -> index_line;
		j++;
		data -> index_line = j;
	}
}

void	process_other_cases(t_data *data, int j, int i, t_lexer **lexer)
{
	if (data->line[j] && search_operators(data->line[j]) == 0)
	{
		str_operators(data, j, i, lexer);
		j = data->index_line;
		i = j;
	}
	if (search_operators(data->line[j]) == 1 && j == 0)
	{
		add_node(data, i, j, lexer);
		j = data->index_line;
		j++;
		data->index_line = j;
	}
	else if (search_operators(data->line[j]) == 1
		&& (data->line[j - 1] != '"' || data->line[j - 1] != 39))
	{
		if (data->line[j] == '\0' || data->line[j] == ' ')
			return ;
		add_node(data, i, j, lexer);
		j = data->index_line;
		j++;
		data->index_line = j;
	}
}

void	str_quotes_operators(t_data *data, int j, int i, t_lexer **lexer)
{
	if (data -> line[j] == '"')
		process_double_quotes(data, &j, i, lexer);
	if (data -> line[j] == 39)
		process_single_quotes(data, &j, i, lexer);
	process_other_cases(data, j, i, lexer);
}

void	identify_line(t_data *data, t_lexer **lexer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data -> line[j])
	{
		skip_whitespace(data, data -> line, j);
		j = data -> index_line;
		i = j;
		if (data -> line[j] == '\0')
			break ;
		str_quotes_operators(data, j, i, lexer);
		j = data -> index_line;
		i = j;
	}
	data -> index_line = 0;
	expander(data, lexer);
	purge_quotes(data, lexer);
}
