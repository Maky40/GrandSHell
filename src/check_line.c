/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:40:16 by xav               #+#    #+#             */
/*   Updated: 2024/03/02 15:53:16 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void check_whitespace(t_data *data)
{
	int	i;

	i = 0;
	while ((data->line[i] >= 9 && data->line[i] <= 13) || (data->line[i] == ' ' && data->line[i] != '\0'))
		i++;
	if (data->line[i] == '\0' || data->line[i] == '|')
	{
		data->valid_line = 1; 
		return ; 
	}
	return ; 	
}



void check_line(t_data *data)
{
	int	i; 
	int inside_quotes = 0; 
	char quote_type = '\0';
	
	i = -1;
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
	check_whitespace(data);
	if (data->valid_line == 1)
	{
		data->exit_status = 0;
		return ; 
	}
	check_line(data);
	if (data->valid_line == 1)
	{
		data->exit_status = 127;
		return ; 
	}
}

