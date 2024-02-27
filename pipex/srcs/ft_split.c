/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:49:29 by xberger           #+#    #+#             */
/*   Updated: 2023/11/24 15:43:20 by xberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **str, int i)
{
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free(str);
	return (0);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*putword(char *word, const char *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**split_words(char const *s, char c, char **str, int nb_words)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	word_len = 0;
	while (word < nb_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		str[word] = (char *)malloc(sizeof(char) *(word_len + 1));
		if (!str[word])
			return (ft_free(str, word));
		putword(str[word], s, i, word_len);
		word_len = 0;
		word++;
	}
	str[word] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	unsigned int	nb_words;

	if (!s)
		return (0);
	nb_words = count_words(s, c);
	str = (char **)malloc(sizeof (char *) * (nb_words + 1));
	if (!str)
		return (NULL);
	str = split_words(s, c, str, nb_words);
	return (str);
}
