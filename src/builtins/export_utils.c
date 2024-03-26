/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:20:40 by mnie              #+#    #+#             */
/*   Updated: 2024/03/26 10:41:49 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	search_variable(char **tab, char *variable)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if ((ft_strncmp(variable, tab[i], ft_strlen(variable)) == 0) && \
		(tab[i][ft_strlen(variable)] == '=' || tab[i][ft_strlen(variable)] == '\0'))
				return (i);
		i++;
	}
	return (-1);
}

char	before_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (str[i - 1]);
}