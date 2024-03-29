/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byebye_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:40:45 by xav               #+#    #+#             */
/*   Updated: 2024/03/29 15:08:23 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *str_without_all_quotes(t_lexer *dup, char *new_str)
{
	int i;
	int j;
	
	i = -1;
	j = 0;
	while (dup->str[++i])
	{
		if (dup->str[i] == '"')
		{
			while (dup->str[++i] != '"')
				new_str[j++] = dup->str[i];
		}
		else if(dup->str[i] == '\'')
		{
			while (dup->str[++i] != '\'')
				new_str[j++] = dup->str[i];
		}
		else
			new_str[j++] = dup->str[i];
	}
	new_str[j] = '\0';
	return (new_str);
}
void malloc_new_str(t_lexer *dup, int i, int j)
{
	char	*new_str;
	
	i = i - j;
	new_str = (char *)malloc(sizeof(char) *(i + 1));
	new_str = str_without_all_quotes(dup, new_str);
	free(dup->str);
	dup->str = new_str;
	
}

void	check_delete_quotes(t_lexer *dup)
{
	int i;
	int j; 

	i = 0;
	j = 0; 
	while (dup->str[i])
	{
		if (dup->str[i] == '"')
		{
			i++;
			while (dup->str[i] != '"')
				i++;
			j += 2;
		}
		else if(dup->str[i] == '\'')
		{
			i++;
			while (dup->str[i] != '\'')
				i++;
			j += 2;
		}
		i++;
	}
	malloc_new_str(dup, i, j);
}
void	purge_quotes(t_data *data, t_lexer **lexer)
{
	t_lexer	*dup;

	(void)data;
	dup = *lexer;
	while (dup)
	{
		dup->in_dq = 0;
		dup->in_sq = 0;
		while (((dup->str[0] == '"' && dup->str[1] == '"') 
			|| (dup->str[0] == '\'' && dup->str[1] == '\'')) && dup->next != NULL)
			dup = dup->next;
		if (dup == NULL)
			break;
		check_delete_quotes(dup);
		dup = dup->next;
	}
}
