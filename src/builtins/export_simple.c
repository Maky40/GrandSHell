/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:23:55 by mnie              #+#    #+#             */
/*   Updated: 2024/03/25 23:41:24 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*add_line_quote(char **tab_tmp, int i)
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
	return(new_line);
}

void	print_sort_env(char **tab_tmp)
{
	char	*swap;
	int		i;

	i = 0;
	while (tab_tmp[i + 1])
	{
		if (ft_strncmp(tab_tmp[i], tab_tmp[i + 1], ft_strlen(tab_tmp[i])) > 0)
		{
			swap = tab_tmp[i + 1];
			tab_tmp[i + 1] = tab_tmp[i];
			tab_tmp[i] = swap;
			i = -1;
		}
		i++;
	}
	i = 0;
	while (tab_tmp[i])
	{
		if (find_equal(tab_tmp[i]) == 1)
			tab_tmp[i] = add_line_quote(tab_tmp, i);
		if (ft_strncmp(tab_tmp[i], "_=", 2) != 0)
			ft_printf("declare -x %s\n", tab_tmp[i]);
		i++;
	}
}

void	export_simple(char **tab)
{
	char	**tab_tmp;

	tab_tmp = dup_env(tab);
	print_sort_env(tab_tmp);
	free_dup_env(tab_tmp);
}