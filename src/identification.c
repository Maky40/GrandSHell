/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:21:27 by mnie              #+#    #+#             */
/*   Updated: 2024/03/30 11:16:26 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void free_lexer(t_lexer **lexer)
{
    t_lexer *lst;
    t_lexer *next_node;

    if (!lexer || !(*lexer))
        return;

    lst = *lexer;
    while (lst)
    {
        next_node = lst->next;
        free(lst->str);
        free(lst);
        lst = next_node;
    }

    *lexer = NULL;
}


int		*add_quote_space(t_data *data, int j)
{
	int	i;
	int	*new;

	i = 0;
	if (data -> quote_space == NULL)
	{
		new = malloc(sizeof(int) * 2);
		new[0] = j;
		new[1] = '\0';
	}
	else
	{
		while (data -> quote_space[i])
			i++;
		new = malloc (sizeof(int) * (i + 2));
		i = -1;
		while (data -> quote_space[++i])
			new[i] = data -> quote_space[i];
		new[i] = j;
		new[i + 1] = '\0';
		free (data -> quote_space);
	}
	return (new);
}
void	skip_whitespace(t_data *data, char *str, int j)
{

	while ((str[j] >= 7 && str[j] <= 13) || str[j] == ' ')
		j++;
	data -> index_line = j;
	if (str[j] == '"' || str[j] == 39)
		data -> quote_space = add_quote_space(data, j);
	return ;
}

int		search_operators(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ' ' || c == '\0')
		return (1);
	return (0);
}
void	str_operators(t_data *data, int j, int i, t_lexer **lexer)
{

	if (data -> line[j] == '"' || data -> line[j] == 39)
		j++;
	while (data -> line[j] != '|' && data -> line[j] != '>' && \
	data -> line[j] != '<' && data -> line[j] != '&' && data -> line[j] && \
	data -> line[j] != ' ' && data -> line[j] != '"' && data -> line[j] != 39 &&\
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

void	str_quotes_operators(t_data *data, int j, int i, t_lexer **lexer)
{
	if (data -> line[j] == '"')
		process_double_quotes(data, &j, i, lexer);
	if (data -> line[j] == 39)
		process_single_quotes(data, &j, i, lexer);
	if (data ->line[j] && search_operators(data ->line[j]) == 0)
	{
		str_operators(data, j, i, lexer);
		j = data -> index_line;
		i = j;
	}
	if (search_operators(data -> line[j]) == 1 && (data -> line[j - 1] != '"' || \
	data -> line[j - 1] != 39))
	{
		if (data -> line[j] == '\0' || data -> line[j] == ' ')
			return ;
		add_node(data, i, j, lexer);
		j = data -> index_line;
		j++;
		data -> index_line = j;
		i = j;
	}
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
	t_lexer *print;
	print = *lexer;
	while(print)
	{
		ft_printf("str = %s, type = %d\n", print -> str, print -> token);
		print = print -> next;
	}
	expander(data, lexer);
	purge_quotes(data,lexer);
}

// revoir la structure de ta fct identify_line + creer les fonctions add_nodes
//  ajouter les returns quand tu creer des nodes
