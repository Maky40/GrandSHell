/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:14:47 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:59:32 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	unsigned int	j;

	i = 0;
	j = ft_strlen(s);
	if (len > j - start)
		len = j - start;
	if (start > j - 1)
		str = (char *)malloc(1);
	else
		str = (char *)malloc(len + 1);
	if (!(str) || !s)
		return (NULL);
	while (i < len && start < j)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
/*#include "stdio.h"

int	main()
{
	char	s[10] = "0123456789";
	char	*str;
	str = ft_substr(s, 7, 5);
	printf("%s", str);
}*/
