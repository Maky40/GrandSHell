/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:49:45 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:58:00 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del)
		return ;
	if (lst != NULL)
	{
		del (lst -> content);
		free (lst);
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
    // Création d'un élément
    t_list *elem1 = ft_lstnew("Élément à supprimer");

    // Suppression de l'élément et libération de la mémoire
    ft_lstdelone_bonus(elem1, free);

    // Affichage du résultat
    printf("Élément supprimé : ");
    print_string(elem1); // Devrait afficher (null)

    return 0;
}*/
