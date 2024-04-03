/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:33:02 by mnie              #+#    #+#             */
/*   Updated: 2024/04/03 15:27:52 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_spe_strjoin(char *s1, char *s2)
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
	free(s2);
	return (new_text);
}

char	*add_variable(char **tab, char *str, int pos)
{
	int		i;
	int		j;
	int		len_str;
	char	*after_equal;

	if (find_equal(tab[pos]) == 1)
	{
		i = 0;
		while (str[i] != '=')
			i++;
		len_str = ft_strlen(str);
		after_equal = malloc(sizeof(char) * (len_str - i));
		i++;
		j = i;
		while (i < len_str)
		{
			after_equal[i - j] = str[i];
			i++;
		}
		after_equal[i - j] = '\0';
		return (ft_spe_strjoin(tab[pos], after_equal));
	}
	return (ft_strdup(str));
}

char	*variable_without_plus(char *str)
{
	int		i;
	int		len;
	int		pos;
	char	*new_str;

	i = -1;
	len = -1;
	while (str[++len])
	{
		if (str[len] == '=')
		{
			pos = len;
			break ;
		}
	}
	while (str[len])
		len++;
	new_str = malloc(sizeof(char) * (len));
	while (++i < pos - 1)
		new_str[i] = str[i];
	i = i - 1;
	while (++i < len)
		new_str[i] = str[i + 1];
	return (new_str);
}

char	*variable_without_plus_equal(char *str)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = 0;
	while (str[len] != '=')
		len++;
	new_str = malloc(sizeof(char) * (len));
	while (i < len - 1)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*variable_without_equal(char *str)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = 0;
	if (find_equal(str) == 0)
	{
		new_str = ft_strdup(str);
		return (new_str);
	}
	while (str[len] != '=')
		len++;
	new_str = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
