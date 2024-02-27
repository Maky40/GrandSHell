/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:46:46 by mnie              #+#    #+#             */
/*   Updated: 2024/02/02 15:26:38 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char		*new_text;
	size_t		size_text_s1;
	size_t		size_text_s2;

	size_text_s1 = ft_strlen(s1);
	size_text_s2 = ft_strlen(s2);
	new_text = ft_calloc(sizeof(char), ((size_text_s1 + size_text_s2) + 1));
	if (new_text == NULL)
		return (NULL);
	ft_strlcpy(new_text, s1, size_text_s1 + 1);
	ft_strlcat(new_text, s2, size_text_s2 + size_text_s1 + 1);
	free(s1);
	return (new_text);
}
