/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:25:38 by mnie              #+#    #+#             */
/*   Updated: 2024/04/03 15:26:01 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_pwd(t_command *cmd, t_data *data)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
	data->exit_status = 0;
}
