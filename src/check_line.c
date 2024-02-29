/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:40:16 by xav               #+#    #+#             */
/*   Updated: 2024/02/29 15:08:51 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



void check_line(t_data *data)
{
	int	i = 0; 
	int inside_quotes = 0; 
	char quote_type = '\0';
	
	while(data->line[i])
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
		i++;
	}
	if (inside_quotes == 1)
	{
		printf("erreur dans les quotes\n");
		exit(1);
	}
}

