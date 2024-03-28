/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:43:17 by mnie              #+#    #+#             */
/*   Updated: 2024/03/27 14:49:12 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const	char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*#include <stdio.h>
int   main(void)
{
        printf("%d\n", ft_strncmp("123", "1245", 4));
        printf("%d\n", ft_strncmp("1243", "1245", 3));
        printf("%d\n", ft_strncmp("11123", "1245",8 ));
		printf("%d\n", ft_strncmp("11123", "1245",-1 ));
		printf("%d\n", strncmp("11123", "1245",-1 ));
		printf("%d\n", ft_strncmp("test\200", "test\0", 6));
		printf("%d\n", strncmp("test\200", "test\0", 6));
}*/
