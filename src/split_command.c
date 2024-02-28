/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:19:41 by xav               #+#    #+#             */
/*   Updated: 2024/02/28 12:21:48 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_free_command(char **split, int word)
{
	while (word != -1)
	{
		free(split[word]);
		word--;
	}
	return (0);
}

int	count_words_command(const char *str, char charset)
{
	int	i;
	int	words;
	int inside_quotes;
	char quote_type;

	inside_quotes = 0;
	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!inside_quotes)
			{
				inside_quotes = 1;
				quote_type = str[i];
			}
			else if(str[i] == quote_type)
			{
				inside_quotes = 0;
				quote_type = '\0';
				words++;
			}
		}
		else if ((str[i + 1] == charset || str[i + 1] == '\0') \
		&& (str[i] != charset && str[i] != '\0' && !inside_quotes))
			words++;
		i++;
	}
	printf("Nombre de mots : %d\n", words);
	return (words);
}

void	write_word_command(char *dest, const char *from, char charset)
{
	int		i;
	int		inside_quotes;
	char	quote_type;

	inside_quotes = 0;
	i = 0;
	quote_type = '\0';
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

int	write_split_command(char **split, const char *str, char charset)
{
	int		i;
	int		j;
	int		word;
	int 	inside_quotes;
	char	quote_type;

	inside_quotes = 0;
	word = 0;
	i = 0;
	quote_type = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == charset && !inside_quotes)
			i++;
		else
		{
			j = 0;
			while ((str[i + j] != charset || inside_quotes) && str[i + j] != '\0')
			{
				if (str[i + j] == '\'' || str[i + j] == '"')
				{
					inside_quotes = 1; 
					quote_type = str[i + j];
				}
				else if (str[i + j] == quote_type)
				{
					inside_quotes = 0; 
					quote_type = '\0';
				}
				j++;
			}
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

char	**ft_split_command(char *str, char c)
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
	free(str);
	return (split);
}
