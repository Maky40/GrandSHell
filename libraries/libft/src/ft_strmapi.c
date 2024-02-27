/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:16:36 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:59:15 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	unsigned int	len;

	str = ft_strdup(s);
	if (!str)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
