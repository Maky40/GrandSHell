/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byebye_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:40:45 by xav               #+#    #+#             */
/*   Updated: 2024/03/25 11:47:32 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *str_without_quotes(t_lexer *dup, char quote_type, char *new_str)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (dup->str[i])
	{
		if (dup->str[i] != quote_type)
		{
			new_str[j] = dup->str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	delete_quotes(t_lexer *dup, char quote_type)
{
	char	*new_str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (dup->str[i])
	{
		if (dup->str[i] == quote_type)
			j++;
		i++;
	}
	i = i - j;
	new_str = (char *)malloc(sizeof(char) *(i + 1));
	new_str = str_without_quotes(dup, quote_type, new_str);
	free(dup->str);
	dup->str = new_str;
	printf("new_str delete quotes : %s\n", dup->str);
}

void	purge_quotes(t_data *data, t_lexer **lexer)
{
	t_lexer	*dup;

	(void)data;
	dup = *lexer;
	while (dup)
	{
		if (!(dup->str[0] == '"' && dup->str[1] == '"'))
			delete_quotes(dup, '"');
		else if (!(dup->str[0] == '\'' && dup->str[1] == '\''))
			delete_quotes(dup, '\'');
		dup = dup->next;
	}
}
