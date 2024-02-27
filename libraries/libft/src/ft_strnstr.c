/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:47:52 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:59:21 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	s_little;

	i = 0;
	s_little = ft_strlen(little);
	if (little[i] == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (big[i + j] && big [i + j] == little[j] && i + j < len)
				j++;
		}
		if (j == s_little)
			return ((char *)big + i);
		else
			i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int main()
{
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "lorem", 15));
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "sit", 5));
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "ipsum", 10));
}*/
