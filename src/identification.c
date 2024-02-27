/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:21:27 by mnie              #+#    #+#             */
/*   Updated: 2024/02/27 17:55:20 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		search_operators(char *str)
{
	if (str[0] == '|' && str[1] == '\0')
		return (1);
	if ((ft_strchr(str, "&&") || ft_strchr(str, "||")) && ft_strlen(str) == 2)
		return (1);
	return (0);
}

void	set_commands(char **split, t_table *all_commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < all_commands -> num_commands)
	{
		all_commands -> commands[i].command = ft_strdup(split[j]);
		ft_printf("command %d = %s\n", i, all_commands -> commands[i].command);
		while (split[j] && search_operators(split[j]) != 1)
			j++;
		j++;
		i++;
	}
	return ;
}

void	define_commands(t_table *all_commands, char **split)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (split[i])
	{
		if (search_operators(split[i]) == 1 && split[i + 1])
			nb++;
		i++;
	}
	ft_printf("nombre = %d\n", nb);
	all_commands -> commands = malloc(sizeof(t_command) * nb);
	all_commands -> num_commands = nb;
	set_commands(split, all_commands);
	return ;
}

void	identify_line(t_data *data)
{
	t_table	all_commands;
	char	**split;

	split = ft_split(data -> line, ' ');
	define_commands(&all_commands, split);
}
