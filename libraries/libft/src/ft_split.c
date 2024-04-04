/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:31:48 by mnie              #+#    #+#             */
/*   Updated: 2024/04/03 16:03:49 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdlib.h>

int	ft_free(char **split, int word)
{
	while (word != -1)
	{
		free(split[word]);
		word--;
	}
	return (0);
}

int	count_words(const char *str, char charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i + 1] == charset || str[i + 1] == '\0') \
		&& (str[i] != charset && str[i] != '\0'))
			words++;
		i++;
	}
	return (words);
}

void	write_word(char *dest, const char *from, char charset)
{
	int	i;

	i = 0;
	while (from[i] != charset && from[i] != '\0')
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

int	write_split(char **split, const char *str, char charset)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == charset)
			i++;
		else
		{
			j = 0;
			while (str[i + j] != charset && str[i + j] != '\0')
				j++;
			split[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (split[word] == NULL)
				return (ft_free(split, word));
			write_word(split[word], str + i, charset);
			i = i + j;
			word++;
		}
	}
	return (1);
}

char	**ft_split(char *str, char c)
{
	char	**split;
	int		words;

	if (!str)
		return (NULL);
	words = count_words(str, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	split[words] = 0;
	if (write_split(split, str, c) == 0)
		return (NULL);
	return (split);
}
