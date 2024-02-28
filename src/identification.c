/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:21:27 by mnie              #+#    #+#             */
/*   Updated: 2024/02/28 15:16:57 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_whitespace(t_data *data, char *str, int j)
{
	while ((str[j] >= 7 && str[j] <= 13) || str[j] == ' ')
		j++;
	data -> index_line = j;
	return ;
}

int		search_operators(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ' ' || c == '\0')
		return (1);
	return (0);
}
void	str_operators(t_data *data, int j, int i)
{
	while (data -> line[j] != '|' && data -> line[j] != '>' && \
	data -> line[j] != '<' && data -> line[j] != '&' && data -> line[j] && \
	data -> line[j] != ' ' && data -> line[j] != '"' && data -> line[j] != 39)
		j++;
	if (data -> line[j] == '"' || data -> line[j] == 39)
		str_quotes(data, j, i);
	add_node(data, i, j - 1);
	if (data -> line[j] == '|')
		add_node(data, i, j);
	if (data -> line[j] == '>')
		add_node(data, i, j);
	if (data -> line[j] == '<')
		add_node(data, i, j);
	if (data -> line[j] == '&')
		add_node(data, i, j);
	if (data -> line[j] == ' ')
		add_node(data, i, j);

}
void	str_quotes(t_data *data, int j, int i)
{
	if (data -> line[j] == '"')
	{
		while (data -> line[j] && data -> line[j] != '"')
			j++;
		if (data -> line[j] == '\0')
			finish_quote();
		// add_node(*data, i, j);
		j++;
		data -> index_line = j;
	}
	if (data -> line[j] == 39)
	{
		while (data -> line[j] && data -> line[j] != 39)
			j++;
		if (data -> line[j] == '\0')
			finish_quote();
		// add_node(data, i, j);
		j++;
		data -> index_line = j;
	}
	if (data ->line[j] && search_operators(data ->line[j]) == 0)
		str_operators(data, j, i);
	if (search_operators(data ->line[j]) == 1)
		add_node(data, j, i);
	return ;
}
void	identify_line(t_data *data, t_lexer *lexer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data -> line[j])
	{
		skip_whitespaces(data, data -> line, j);
		j = data -> index_line;
		i = j;
		str_quotes(data, j, i);
		j = data -> index_line;
		i = j;
		str_operators(data, j, i);
	}
	return ;
}
// revoir la structure de ta fct identify_line + creer les fonctions add_nodes
//  ajouter les returns quand tu creer des nodes
