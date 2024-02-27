/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:43:34 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:58:24 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!src && !dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = *((unsigned char *)(src + i));
		i++;
	}
	return (dest);
}
