/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:10:58 by mnie              #+#    #+#             */
/*   Updated: 2024/03/21 14:25:39 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_printf_error_export(char *str)
{
	ft_printf("%s\n", str);
	return (1);
}


int		ft_error_export(char *str)
{
	char *quote;

	quote = malloc(sizeof(char) * 2);
	quote[0] = '"';
	quote[1] = '\0';
	if (ft_strchr(str, " ") == 1)
		return (ft_printf_error_export("ERROR"));
	if (ft_isdigit(str[0]) != 1)
		return (ft_printf_error_export("ERROR"));
	if (ft_strchr(str, "'") == 1 && ft_strchr(str, quote) == 1)
		return (ft_printf_error_export("ERROR"));
	return (0);
}

char	before_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '=')
		i++;
	return (str[i - 1]);
}

char	*ft_dup_var(char *str)
{
	int		i;
	char	*var;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	if (str[i - 1] == '-' || str[i - 1] == '+')
		i--;
	var = malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	while (j < i)
	{
		var[j] = str[j];
		j++;
	}
	return (var);
}

int	search_variable(char **env, char *variable)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (env[i])
	{
		if (ft_strncmp(variable, env[i], ft_strlen(variable)) == 0 \
			&& env[i][ft_strlen(variable)] == '=')
				k = 1;
		i++;
	}
	return (k);
}