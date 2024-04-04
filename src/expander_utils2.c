/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:59:50 by xav               #+#    #+#             */
/*   Updated: 2024/04/04 15:57:36 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_signal;

char	*get_exit_status(t_data *data)
{
	char	*ret;

	if (g_signal != -1)
		ret = ft_itoa(130);
	else
		ret = ft_itoa(data->exit_status);
	return (ret);
}

void	free_and_null(t_lexer *dup)
{
	free(dup->str);
	dup->str = NULL;
}
