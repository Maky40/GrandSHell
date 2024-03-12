/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:28:18 by mnie              #+#    #+#             */
/*   Updated: 2024/03/12 16:37:05 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_data(t_data *data)
{
	free(data -> line);
	free(data -> quote_space);
	free_dup_env(data -> env);
	free (data);
}

int	verify_line(t_lexer **lexer)
{
	t_lexer	*lst;

	lst = *lexer;
	while (lst)
	{
		if (lst -> token == INPUT)
		{
			if (lst -> next != NULL && lst -> next -> token != FD)
				return (1);
		}
		lst = lst -> next;
	}
	return (0);
}

void	free_all(t_data *data, t_data **lexer)
{
	free_lexer(lexer);
	free_data(data);
}