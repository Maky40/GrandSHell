/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:02:17 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:58:10 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst -> content));
		if (!node)
		{
			ft_lstdelone(node, del);
			ft_lstclear(&new_list, del);
			return (new_list);
		}
		ft_lstadd_back(&new_list, node);
		lst = lst -> next;
	}
	return (new_list);
}
