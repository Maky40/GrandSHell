/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:06:29 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:57:50 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last -> next = new;
}
/*
#include <stdio.h>
int main()
{
    // Création de la liste et de nouveaux éléments
    t_list *lst = NULL;
    t_list *elem1 = ft_lstnew("Premier élément");
    t_list *elem2 = ft_lstnew("Deuxième élément");
    t_list *elem3 = ft_lstnew("Troisième élément");

    // Ajout des éléments à l'arrière de la liste
    ft_lstadd_back_bonus(&lst, elem1);
    ft_lstadd_back_bonus(&lst, elem2);
    ft_lstadd_back_bonus(&lst, elem3);

    // Affichage des éléments de la liste
    t_list *current = lst;
    while (current)
    {
        printf("%s\n", (char *)(current->content));
        current = current->next;
    }

    // Libération de la mémoire
    ft_lstclear_bonus(&lst, free);
    return 0;
}*/
