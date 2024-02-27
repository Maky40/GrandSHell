/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:44:33 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:59:27 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isset(char const s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	while (ft_isset(s1[i], set) != 0 && i < len)
		i++;
	if (i == len)
		return (0);
	return (i);
}

int	ft_end(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (ft_isset(s1[i], set) == 1 && i != 0)
		i--;
	if (i == 0 && ft_isset(s1[i], set) == 1)
		return (i);
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1)
		return (NULL);
	end = ft_end(s1, set);
	start = ft_start(s1, set);
	len = (end - start - 1) + 1;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	end = 0;
	while (end < len)
	{
		str[end] = s1[start + end];
		end++;
	}
	str[end] = '\0';
	return (str);
}

/*#include <stdio.h>

int	main()
{
	char *s1 = "abcfbcabbb";
	//char *s2 = "";
    char *ret = ft_strtrim(s1, "abc");
	printf("%s", ret);
}*/
