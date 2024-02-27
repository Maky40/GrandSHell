/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:14:36 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:57:53 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
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

    // Ajout des éléments en tête de la liste
    ft_lstadd_front_bonus(&lst, elem3);
    ft_lstadd_front_bonus(&lst, elem2);
    ft_lstadd_front_bonus(&lst, elem1);

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
