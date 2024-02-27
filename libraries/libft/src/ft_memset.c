/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:48:27 by mnie              #+#    #+#             */
/*   Updated: 2023/10/09 13:10:31 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}
/*#include <stdio.h>
int main()
{
	char s[8] = "aaaaaaad";
	size_t	n;

	n = 4;
	printf("%p\n\n", ft_memset((void *)s,'b',n));
	printf("%s", s);
}*/
