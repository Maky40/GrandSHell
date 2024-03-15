/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:11:57 by mnie              #+#    #+#             */
/*   Updated: 2024/03/15 13:43:05 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;

	s2 = (char *)malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!s2)
		return (0);
	ft_memcpy(s2, s, ft_strlen(s) + 1);
	return (s2);
}
