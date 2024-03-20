/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:10:58 by mnie              #+#    #+#             */
/*   Updated: 2024/03/20 14:54:41 by mnie             ###   ########.fr       */
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
	if (ft_strchr(str, " ") == 1)
		return (ft_printf_error_export("ERROR"));
	if (ft_isdigit(str[0]) != 1)
		return (ft_printf_error_export("ERROR"));
	if (ft_strchr(str, "'") == 1 && ft_strchr(str, '"') == 1)
		return (ft_printf_error_export("ERROR"));
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
	str[i] = NULL;
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
	return (k);
}