/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:03:53 by mnie              #+#    #+#             */
/*   Updated: 2024/04/04 10:52:56 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_variable_shlvl(t_data *data, char *str, int j)
{
	int		len;
	char	**new_tab;
	int		i;

	i = 0;
	len = 0;
	while (data -> env[len])
		len++;
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (j == -1)
		j = len;
	while (i < j)
	{
		new_tab[i] = ft_strdup(data -> env[i]);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	while (i + 1 < len + 1)
	{
		new_tab[i + 1] = ft_strdup(data -> env[i]);
		i++;
	}
	new_tab[i + 1] = '\0';
	free_dup_env(data -> env);
	data -> env = new_tab;
}

char	*str_shllvl(int j, int value)
{
	char	*str;
	int		i;
	char	*num;
	int		k;

	str = malloc(sizeof(char) * (6 + j + 1));
	str[0] = 'S';
	str[1] = 'H';
	str[2] = 'L';
	str[3] = 'V';
	str[4] = 'L';
	str[5] = '=';
	i = 6;
	num = ft_itoa(value);
	k = 0;
	while (num[k])
	{
		str[i + k] = num[k];
		k++;
	}
	str[i + k] = '\0';
	free(num);
	return (str);
}

void	modified_shllvl(t_data *data, int pos, int value, char *str_search)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	if (pos > -1)
	{
		i = value;
		while (i != 0)
		{
			j++;
			i /= 10;
		}
	}
	else
		j = 1;
	str = str_shllvl(j, value);
	find_and_remove(data -> env, str_search);
	create_variable_shlvl(data, str, pos);
	free(str);
}

void	maj_shlvl(t_data *data, char **envp)
{
	int		pos;
	int		i;
	int		value;
	char	*str_search;

	str_search = malloc(sizeof(char) * 6);
	str_search[0] = 'S';
	str_search[1] = 'H';
	str_search[2] = 'L';
	str_search[3] = 'V';
	str_search[4] = 'L';
	str_search[5] = '\0';
	pos = search_variable(envp, str_search);
	if (pos > -1)
	{
		i = 0;
		while ((envp[pos][i] < '0' || envp[pos][i] > '9') && envp[pos][i])
			i++;
		if (ft_alldigit(envp[pos] + i) == 1)
			value = ft_atoi((envp[pos] + i)) + 1;
	}
	if (pos == -1 || value < 2)
		value = 2;
	modified_shllvl(data, pos, value, str_search);
	free (str_search);
}
