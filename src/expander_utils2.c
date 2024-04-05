/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:59:50 by xav               #+#    #+#             */
/*   Updated: 2024/04/05 14:28:59 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_signal;

void	set_command(t_lexer *lst, t_table *tab_cmds, int i)
{
	if (lst->str != NULL)
		tab_cmds -> commands[i].command = ft_strdup(lst -> str);
	else
		tab_cmds -> commands[i].command = NULL;
}

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
