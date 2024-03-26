/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byebye_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:40:45 by xav               #+#    #+#             */
/*   Updated: 2024/03/26 17:13:48 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *str_without_all_quotes(t_lexer *dup, char *new_str)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (dup->str[i])
	{
		if (dup->str[i] != '"' && dup->str[i] != 39)
		{
			new_str[j] = dup->str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char *str_without_quotes(t_lexer *dup, char *new_str, char quote_type)
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

void	delete_single_quotes(t_lexer *dup)
{
	char	*new_str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (dup->str[i])
	{
		if (dup->str[i] == 39)
			j++;
		i++;
	}
	i = i - j;
	new_str = (char *)malloc(sizeof(char) *(i + 1));
	new_str = str_without_quotes(dup, new_str, '\'');
	free(dup->str);
	dup->str = new_str;
}
void	delete_double_quotes(t_lexer *dup)
{
	char	*new_str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (dup->str[i])
	{
		if (dup->str[i] == '"')
			j++;
		i++;
	}
	i = i - j;
	new_str = (char *)malloc(sizeof(char) *(i + 1));
	new_str = str_without_quotes(dup, new_str, '"');
	free(dup->str);
	dup->str = new_str;
}

void	delete_all_quotes(t_lexer *dup)
{
	char	*new_str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (dup->str[i])
	{
		if (dup->str[i] == '"' || dup->str[i] == 39)
			j++;
		i++;
	}
	i = i - j;
	new_str = (char *)malloc(sizeof(char) *(i + 1));
	new_str = str_without_all_quotes(dup,new_str);
	free(dup->str);
	dup->str = new_str;

}

void	check_delete_quotes(t_lexer *dup)
{
	if (dup->in_dq == 0 && dup->in_sq == 0)
		delete_all_quotes(dup);
	else if (dup->in_dq == 1)
		delete_double_quotes(dup);
	else if (dup->in_sq == 1)
		delete_single_quotes(dup);
		
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
		if (dup->str[0] == '"')
			dup->in_dq = 1;
		else if (dup->str[0] == 39)
			dup->in_sq = 1;
		check_delete_quotes(dup);
		dup = dup->next;
	}
}
