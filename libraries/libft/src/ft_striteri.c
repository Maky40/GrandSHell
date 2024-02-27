/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:37:32 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:58:58 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;
	int	j;

	if (!(s == NULL) && !(f == NULL))
	{
		i = 0;
		j = ft_strlen(s);
		while (i < j)
		{
			f(i, s + i);
			i++;
		}
	}
}
