/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:11:57 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:58:56 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;

	s2 = (char *)malloc((ft_strlen(s) + 1));
	if (!s2)
		return (0);
	ft_memcpy(s2, s, ft_strlen(s) + 1);
	return (s2);
}
