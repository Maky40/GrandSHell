/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:16:21 by xberger           #+#    #+#             */
/*   Updated: 2023/10/16 10:54:55 by xberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find == str || *to_find == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		while ((i + j) < n && str[i + j] == to_find[j])
		{
			if (str[i + j] == '\0' && to_find[j] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
