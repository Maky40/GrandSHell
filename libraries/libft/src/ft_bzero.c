/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:43:20 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:57:12 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *) s + i) = 0;
		i++;
	}
}
/*#include <stdio.h>
int	main()
{
	char s[6] = "123456";
	ft_bzero((void *)s, 3);
	printf("%c%c%c%C%c%c", s[0], s[1], s[2], s[3], s[4], s[5]);
}*/
