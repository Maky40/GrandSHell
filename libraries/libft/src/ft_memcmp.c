/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:51:47 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:58:22 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/*#include <stdio.h>
int	main()
{
	char	a[5] = "ABCDE";
	char	b[4] = "ABCD";
	char	c[5] = "";

	printf("%d ; %d ; %d", ft_memcmp((const void *)a, (const void *)b, 5), \
	ft_memcmp((const void *)a, (const void *)b, 4), \
	ft_memcmp((const void *)a, (const void *)c, 5));
}*/
