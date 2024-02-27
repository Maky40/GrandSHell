/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:52:59 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:57:57 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;

	if (!lst || !*lst || !del)
		return ;
	while (lst && *lst)
	{
		list = (*lst)-> next;
		ft_lstdelone(*lst, del);
		(*lst) = list;
	}
}
/*
#include <stdio.h>
void print_string(void *content)
{
    if (content)
        printf("%s\n", (char *)content);
}

int main()
{
    // Création de la liste et d'éléments
    t_list *lst = NULL;
    t_list *elem1 = ft_lstnew("Premier élément");
    t_list *elem2 = ft_lstnew("Deuxième élément");
    t_list *elem3 = ft_lstnew("Troisième élément");

    // Ajout des éléments à la liste
    ft_lstadd_back(&lst, elem1);
    ft_lstadd_back(&lst, elem2);
    ft_lstadd_back(&lst, elem3);

    // Affichage des éléments de la liste avant suppression
    printf("Éléments de la liste avant suppression :\n");
    t_list *current = lst;
    while (current)
    {
        print_string(current->content);
        current = current->next;
    }

    // Suppression de la liste et libération de la mémoire
    ft_lstclear(&lst, free);

    // Affichage des éléments de la liste après suppression
    printf("Éléments de la liste après suppression :\n");
    current = lst;
    while (current)
    {
        print_string(current->content);
        current = current->next;
    }

    return 0;
}*/
