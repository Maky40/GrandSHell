/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:36:23 by xav               #+#    #+#             */
/*   Updated: 2024/03/05 09:37:00 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void check_whitespace(t_data *data)
{
	int	i;

	i = 0;
	if (!data->line)
		return ; 
	while ((data->line[i] >= 9 && data->line[i] <= 13) || (data->line[i] == ' ' && data->line[i] != '\0'))
		i++;
	if (data->line[i] == '\0' || data->line[i] == '|')
	{
		data->valid_line = 1; 
		return ; 
	}
	return ; 	
}



void check_line(t_data *data, int i)
{
	int inside_quotes = 0; 
	char quote_type = '\0';
	
	inside_quotes = 0;
	quote_type = '\0';
	while(data->line[++i])
	{
		if (data->line[i] == '\'' || data->line[i] == '"')
		{
			if (!inside_quotes)
			{
				inside_quotes = 1;
				quote_type = data->line[i];
			}
			else if (data->line[i] == quote_type)
			{
				inside_quotes = 0;
				quote_type = '\0';
			}
		}
	}
	if (inside_quotes == 1)
		data->valid_line = 1;
}

void check_invalid_line(t_data *data)
{
	int i; 

	i = -1;
	if (!data->line)
	{
		data->exit_status = 0;
		return ; 
	}
	check_whitespace(data);
	if (data->valid_line == 1)
	{
		data->exit_status = 0;
		return ; 
	}
	check_line(data, i);
	if (data->valid_line == 1)
	{
		data->exit_status = 127;
		return ; 
	}
}
