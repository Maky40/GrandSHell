/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byebye_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:40:45 by xav               #+#    #+#             */
/*   Updated: 2024/03/20 14:51:03 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void delete_quotes(t_lexer *dup, char quote_type)
{
	char	*new_str;
	int 	j; 
	int		i;

	i = 0;
	j = 0;
	while(dup->str[i])
	{
		if (dup->str[i] == quote_type)
			j++;
		i++;
	}
	i = i - j;
	new_str = (char *)malloc(sizeof(char) *(i + 1));
	i = 0;
	j = 0;
	while(dup->str[i])
	{
		if (dup->str[i] != quote_type)
		{
			new_str[j] = dup->str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(dup->str);
	dup->str = new_str;
	printf("new_str delete quotes : %s\n", dup->str);
}
	


void purge_quotes(t_data *data, t_lexer **lexer)
{
	(void)data;
	t_lexer *dup;

	dup = *lexer;
	while(dup)
	{
		if (dup->str[0] == '"' && dup->str[1] != '"')
			delete_quotes(dup, '"');
		else if (dup->str[0] == '\'' && dup->str[1] != '\'')
			delete_quotes(dup, '\'');
		dup = dup->next;	
	}
}