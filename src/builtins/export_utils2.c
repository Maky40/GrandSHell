/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:33:02 by mnie              #+#    #+#             */
/*   Updated: 2024/03/26 14:54:26 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*add_variable(char **tab, char *str, int pos)
{
	int		i;
	int		j;
	int		len_str;
	char	*after_equal;

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
	if (find_equal(tab[pos]) == 1)
		return (ft_strjoin(tab[pos], after_equal));
	else
		return (ft_strjoin(ft_strjoin(tab[pos], "="), after_equal));
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
	new_str[i] = '\0';
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