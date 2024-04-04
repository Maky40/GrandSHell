/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:23:55 by mnie              #+#    #+#             */
/*   Updated: 2024/04/04 11:06:38 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	modif_shlvl(char **tab_tmp)
{
	int		i;
	char	*str_search;

	i = 0;
	str_search = malloc(sizeof(char) * 7);
	str_search[0] = 'S';
	str_search[1] = 'H';
	str_search[2] = 'L';
	str_search[3] = 'V';
	str_search[4] = 'L';
	str_search[5] = '=';
	str_search[6] = '\0';
	while (tab_tmp[i])
	{
		if (ft_strncmp(str_search, tab_tmp[i], ft_strlen(str_search)) == 0 && \
		ft_strlen(tab_tmp[i]) > 6 && ft_alldigit(tab_tmp[i] + 6) == 1)
			modif_shlvl2(tab_tmp, i, str_search);
		i++;
	}
	free(str_search);
}

char	*add_line_quote2(char **tab_tmp, int i)
{
	char	*new_line;
	int		len;
	int		j;

	j = 0;
	len = ft_strlen(tab_tmp[i]) + 2;
	new_line = malloc(sizeof(char) * len + 1);
	while (tab_tmp[i][j] != '=')
	{
		new_line[j] = tab_tmp[i][j];
		j++;
	}
	new_line[j] = tab_tmp[i][j];
	j++;
	new_line[j] = '"';
	while (tab_tmp[i][j])
	{
		new_line[j + 1] = tab_tmp[i][j];
		j++;
	}
	new_line[j + 1] = '"';
	new_line[j + 2] = '\0';
	free(tab_tmp[i]);
	return (new_line);
}

void	add_line_quote(char **tab_tmp)
{
	int		i;

	i = 0;
	while (tab_tmp[i])
	{
		if (find_equal(tab_tmp[i]) == 1)
			tab_tmp[i] = add_line_quote2(tab_tmp, i);
		if (ft_strncmp(tab_tmp[i], "_=", 2) != 0)
			ft_printf("declare -x %s\n", tab_tmp[i]);
		i++;
	}
}

void	print_sort_env(char **tab_tmp)
{
	char	*swap;
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	while (tab_tmp[i + 1])
	{
		str1 = variable_without_equal(tab_tmp[i]);
		str2 = variable_without_equal(tab_tmp[i + 1]);
		if (ft_strncmp(str1, str2, ft_strlen(str1)) > 0)
		{
			swap = tab_tmp[i + 1];
			tab_tmp[i + 1] = tab_tmp[i];
			tab_tmp[i] = swap;
			i = -1;
		}
		free (str1);
		free (str2);
		i++;
	}
	modif_shlvl(tab_tmp);
	add_line_quote(tab_tmp);
}

void	export_simple(char **tab)
{
	char	**tab_tmp;

	tab_tmp = dup_env(tab);
	print_sort_env(tab_tmp);
	free_dup_env(tab_tmp);
}
