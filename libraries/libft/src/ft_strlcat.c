/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:03:21 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:59:05 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	d = ft_strlen(dst);
	s = 0;
	while (src[s] != '\0' && d < size - 1)
	{
		dst[d] = src[s];
		d++;
		s++;
	}
	dst[d] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[s]));
}
