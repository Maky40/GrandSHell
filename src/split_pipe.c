/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:58:31 by xav               #+#    #+#             */
/*   Updated: 2024/02/29 14:58:15 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_free_pipe(char **split, int word)
{
	while (word != -1)
	{
		free(split[word]);
		word--;
	}
	return (0);
}

int	count_words_pipe(const char *str, char charset)
{
	int	i;
	int	words;
	char	quote_type;
	 
	quote_type = '\0';
	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			quote_type = str[i++];
			while (str[i] != quote_type && str[i])
				i++;
		}
		if ((str[i + 1] == charset || str[i + 1] == '\0') \
		&& (str[i] != charset && str[i] != '\0'))
			words++;
		i++;
	}
	printf("Nb words : %d\n", words);
	return (words);
}

void	write_word_pipe(char *dest, const char *from, char charset)
{
	int	i;
	char quote_type;
	int inside_quotes;

	inside_quotes = 0;
	quote_type = '\0';
	i = 0;
	while ((from[i] != charset || inside_quotes) && from[i] != '\0')
	{
		if (!inside_quotes && (from[i] == '\'' || from[i] == '"'))
		{
			inside_quotes = 1; 
			quote_type = from[i];
		}
		else if (from[i] == quote_type)
		{
			inside_quotes = 0;
			quote_type = '\0';
		}
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

int	write_split_pipe(char **split, const char *str, char charset)
{
	int		i;
	int		j;
	int		word;
	char	quote_type;

	quote_type = '\0';
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
			{
				if ((str[i + j] == '\'' || str[i + j] == '"'))
				{ 
					quote_type = str[i + j];
					j++;
					while (str[i + j] != quote_type)
						j++;
				}				
				j++;
			}
			split[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (split[word] == NULL)
				return (ft_free_pipe(split, word));
			write_word_pipe(split[word], str + i, charset);
			i = i + j;
			word++;
		}
	}
	return (1);
}

char	**ft_split_pipe(char *str, char c)
{
	char	**split;
	int		words;

	if (!str)
		return (NULL);
	words = count_words_pipe(str, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	split[words] = 0;
	if (write_split_pipe(split, str, c) == 0)
		return (NULL);
	free(str);
	int i = 0;
	while(split[i])
	{
		ft_printf("Mot %d : %s\n", (i), split[i]);
		i++;
	}
	return (split);
}