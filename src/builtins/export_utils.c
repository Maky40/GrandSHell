/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:20:40 by mnie              #+#    #+#             */
/*   Updated: 2024/04/02 11:31:14 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
void	ft_error_export2(char *str, t_data *data)
{
	ft_printf("%s\n", str);
	data -> exit_status = 1;
}
int		ft_error_export(char *str, t_data *data)
{
	if (ft_strlen(str) == 1 && str[0] == '$')
	{
		data -> exit_status = 1;
		return (1);
	}
	if (ft_strchr(str, " ") == 1)
	{
		data -> exit_status = 1;
		return (1);
	}
	if (ft_isdigit(str[0]) == 1)
	{
		data -> exit_status = 1;
		return (1);
	}
	if (ft_strchr(str, "'") == 1)
	{
		data -> exit_status = 1;
		return (1);
	}
	return (0);
}

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

*/

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
/*
char	before_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (str[i - 1]);
}
*/
