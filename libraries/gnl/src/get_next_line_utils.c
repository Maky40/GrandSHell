/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:14:07 by mnie              #+#    #+#             */
/*   Updated: 2024/02/05 11:17:58 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

int	ft_found_newline(t_klist *lst)
{
	t_klist	*node;
	int		i;

	if (lst == NULL)
		return (0);
	node = lst;
	while (node -> next != NULL)
		node = node -> next;
	i = 0;
	while (node -> content[i])
	{
		if (node -> content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_klist	*ft_klstlast(t_klist *lst)
{
	t_klist	*last;

	last = lst;
	while (last && last->next)
		last = last->next;
	return (last);
}

int	ft_len_line(t_klist	*lst)
{
	t_klist	*current;
	int		i;
	int		len;

	current = lst;
	len = 0;
	while (current)
	{
		i = 0;
		while (current -> content[i])
		{
			if (current -> content[i] == '\n')
				return (len + 1);
			i++;
			len++;
		}
		current = current -> next;
	}
	return (len);
}

void	ft_free_stock(t_klist *stash)
{
	t_klist	*current;
	t_klist	*new;

	current = stash;
	while (current)
	{
		free(current->content);
		new = current->next;
		free(current);
		current = new;
	}
}

int	ft_strlen2(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
