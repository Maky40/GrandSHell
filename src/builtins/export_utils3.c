/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:03:50 by xav               #+#    #+#             */
/*   Updated: 2024/04/04 11:08:31 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	modif_shlvl2(char **tab_tmp, int i, char *str_search)
{
	int		j;
	int		num;
	char	*new_str;

	j = 0;
	while ((tab_tmp[i][j] < '0' || tab_tmp[i][j] > '9') && tab_tmp[i][j])
		j++;
	if (tab_tmp[i][j] == '\0')
		return ;
	num = ft_atoi((tab_tmp[i] + j)) - 1;
	new_str = ft_itoa(num);
	new_str = ft_spe_strjoin(str_search, new_str);
	free(tab_tmp[i]);
	tab_tmp[i] = ft_strdup(new_str);
	free(new_str);
}

int	ft_alldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*modified_str_shlvl(char *str, char *str_search)
{
	int		i;
	int		num;
	char	*new_str;

	i = 0;
	while ((str[i] < '0' || str[i] > '9') && str[i])
		i++;
	if (str[i] == '\0')
	{
		free(str_search);
		return (ft_strdup(str));
	}
	num = ft_atoi((str + i)) + 1;
	new_str = ft_itoa(num);
	new_str = ft_spe_strjoin(str_search, new_str);
	free(str_search);
	return (new_str);
}

char	*add_str(char *str)
{
	char	*str_search;

	str_search = malloc(sizeof(char) * 7);
	str_search[0] = 'S';
	str_search[1] = 'H';
	str_search[2] = 'L';
	str_search[3] = 'V';
	str_search[4] = 'L';
	str_search[5] = '=';
	str_search[6] = '\0';
	if (ft_strncmp(str_search, str, ft_strlen(str_search)) == 0 && \
	ft_strlen(str) > 6 && ft_alldigit(str + 6) == 1)
		return (modified_str_shlvl(str, str_search));
	free(str_search);
	return (ft_strdup(str));
}
