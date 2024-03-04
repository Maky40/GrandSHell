/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:29:25 by xav               #+#    #+#             */
/*   Updated: 2024/03/04 10:32:57 by xav              ###   ########.fr       */
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