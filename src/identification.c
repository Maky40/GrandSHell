/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:21:27 by mnie              #+#    #+#             */
/*   Updated: 2024/02/29 15:25:47 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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
void	str_operators(t_data *data, int j, int i, t_lexer *lexer)
{
	if (data -> line[j] == '"' || data -> line[j] == 39)
		j++;
	while (data -> line[j] != '|' && data -> line[j] != '>' && \
	data -> line[j] != '<' && data -> line[j] != '&' && data -> line[j] && \
	data -> line[j] != ' ' && data -> line[j] != '"' && data -> line[j] != 39)
		j++;
	if (data -> line[j] == '"' || data -> line[j] == 39)
	{
		ft_printf("Je sui dans str_operators et je repars dans quotes avec i = %d, j = %d\n", i, j);
		str_quotes_operators(data, j, i, lexer);
	}
	else
	{
		ft_printf("------dans str_operators, j'ajoute un noeud pour i = %d et j - 1 = %d\n", i, j - 1);
		i = j;
		// add_node(data, i, j - 1);
		if (data -> line[j] == '|')
		{
			ft_printf("------dans str_operators, j'ajoute un noeud avec | pour i = %d et j = %d \n", i, j);
			// add_node(data, i, j);
		}
		if (data -> line[j] == '>')
		{
			ft_printf("------dans str_operators, j'ajoute un noeud avec > pour i = %d et j = %d \n", i, j);
			// add_node(data, i, j);
		}
		if (data -> line[j] == '<')
		{
			ft_printf("------dans str_operators, j'ajoute un noeud avec < pour i = %d et j = %d \n", i, j);
			// add_node(data, i, j);
		}
		if (data -> line[j] == '&')
		{
			ft_printf("------dans str_operators, j'ajoute un noeud avec & pour i = %d et j = %d \n", i, j);
			// add_node(data, i, j);
		}
		j++;
		data -> index_line = j;
		return ;
	}
}
void	str_quotes_operators(t_data *data, int j, int i, t_lexer *lexer)
{
	static int	k = 1;
	static int	l = 1;

	if (data -> line[j] == '"')
	{
		ft_printf("%d fois boucle double quotes\n", k);
		j++;
		while (data -> line[j] && data -> line[j] != '"')
			j++;
		if (data -> line[j] == '\0')
		{
			// finish_quote();
			ft_printf("QUOTE PAS FINI JE DEMANDE DE TERMINER\n");
		}
		if (search_operators(data ->line[j + 1]) == 1)
		{
			ft_printf("------J'ajoute un node pour i = %d et j = %d\n", i, j);
			ft_printf("------NODE : i = %c -- j = %c\n", data -> line[i], data -> line[j]);
			// add_node(*data, i, j);
			j++;
			data -> index_line = j;
			i = j;
		}
		k++;
	}
	if (data -> line[j] == 39)
	{
		ft_printf("%d fois boucle simple quote\n", l);
		j++;
		while (data -> line[j] && data -> line[j] != 39)
			j++;
		if (data -> line[j] == '\0')
		{
			// finish_quote();
			ft_printf("QUOTE PAS FINI JE DEMANDE DE TERMINER\n");
		}
		if (search_operators(data ->line[j + 1]) == 1)
		{
			ft_printf("------J'ajoute un node pour i = %d et j = %d\n", i, j);
			// add_node(*data, i, j);
			j++;
			data -> index_line = j;
			i = j;
		}
		l++;
	}
	if (data ->line[j] && search_operators(data ->line[j]) == 0)
	{
		ft_printf ("je vais dans str_operators pour i = %d, j = %d\n", i, j);
		str_operators(data, j, i, lexer);
		j = data -> index_line;
		i = j;
	}
	if (search_operators(data -> line[j]) == 1 && (data -> line[j - 1] != '"' || \
	data -> line[j - 1] != 39))
	{
		if (data -> line[j] == '\0' || data -> line[j] == ' ')
			return ;
		ft_printf("------j'ajoute un noeud ca on a la lettre %c \n", data ->line[j]);
		// add_node(data, j, i);
		j++;
		data -> index_line = j;
		i = j;
	}
	return ;
}
void	identify_line(t_data *data, t_lexer *lexer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	lexer = NULL;
	data -> quote_space = NULL;
	while (data -> line[j])
	{
		ft_printf("je rentre dans identify line, i = %d, j = %d\n", i, j);
		skip_whitespace(data, data -> line, j);
		j = data -> index_line;
		i = j;
		ft_printf("je skip whitespace, i = %d, j = %d\n", i, j);
		if (data -> line[j] == '\0')
			break ;
		str_quotes_operators(data, j, i, lexer);
		j = data -> index_line;
		i = j;
	}
}
// revoir la structure de ta fct identify_line + creer les fonctions add_nodes
//  ajouter les returns quand tu creer des nodes
