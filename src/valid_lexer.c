/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:14:37 by xav               #+#    #+#             */
/*   Updated: 2024/04/01 14:34:29 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_lexer(t_data *data, t_lexer **lexer)
{
	t_lexer	*lst;

	lst = *lexer;
	data->valid_lexer = 1;
	while (lst->next != NULL)
	{
		if (lst->token == 1 || lst->token == 2
			|| lst->token == 3 || lst->token == 4)
		{
			if (lst->next->token >= 0 && lst->next->token <= 4)
				data->valid_lexer = 0;
			else if (lst->token == 0)
			{
				if (lst->next->token == 0)
					data->valid_lexer = 0;
			}
		}
		lst = lst->next;
	}
	if (lst->token >= 0 && lst->token <= 4)
		data->valid_lexer = 0;
}
