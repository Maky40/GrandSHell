/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:10:58 by mnie              #+#    #+#             */
/*   Updated: 2024/03/24 21:14:43 by mnie             ###   ########.fr       */
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
	ft_printf("if 1 : %d, if 2 : %d, if 3 : %d - %d\n", ft_strchr(str, " "), ft_isdigit(str[0]), ft_strchr(str, "'"), ft_strchr(str, quote));
	if (ft_strchr(str, " ") == 1)
	{
		free (quote);
		return (ft_printf_error_export("ERROR"));
	}
	if (ft_isdigit(str[0]) == 1)
	{
		free (quote);
		return (ft_printf_error_export("ERROR"));
	}
	if (ft_strchr(str, "'") == 1 && ft_strchr(str, quote) == 1)
	{
		free (quote);
		return (ft_printf_error_export("ERROR"));
	}
	free (quote);
	return (0);
}

char	before_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
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

int	search_variable(t_env *env, char *variable)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (env -> modified_env[i])
	{
		if (ft_strncmp(variable, env -> modified_env[i], ft_strlen(variable)) == 0 \
			&& env -> modified_env[i][ft_strlen(variable)] == '=')
				k = 1;
		i++;
	}
	i = 0;
	while (env -> vars_add[i])
	{
		if (ft_strncmp(variable, env -> vars_add[i], ft_strlen(variable)) == 0)
				k = 2;
		i++;
	}
	return (k);
}