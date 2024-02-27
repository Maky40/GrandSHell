/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:53:09 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:58:16 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst -> next;
	}
	return (i);
}
/*#include <stdio.h>

int main()
{
	// Création de quelques nœuds pour une liste chaînée
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));
	t_list *node3 = malloc(sizeof(t_list));

	// Initialisation des nœuds
	node1->content = "Premier élément";
	node1->next = node2;
	node2->content = "Deuxième élément";
	node2->next = node3;
	node3->content = "Troisième élément";
	node3->next = NULL; // Dernier élément de la liste

	// Appel de ft_lstsize pour compter le nombre d'éléments
	int count = ft_lstsize(node1);

	// Affichage du résultat
	printf("Le nombre d'éléments dans la liste chaînée est : %d\n", count);

	// Libération de la mémoire des nœuds (nettoyage)
	free(node1);
	free(node2);
	free(node3);

	return 0;
}*/
