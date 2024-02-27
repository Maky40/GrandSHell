/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:55:27 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:58:19 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *) s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main()
{
	char	s[10] = "123456789";
	char	*ret;
    printf("%s", (char *)ft_memchr(tab, -1, 7));

	ret = ft_memchr((const void *)s,'7',9);
	printf("%s", ret);
	ret = ft_memchr((const void *)s,'7',2);
	printf("\n%s", ret);
}*/
