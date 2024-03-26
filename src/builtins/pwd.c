/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:25:38 by mnie              #+#    #+#             */
/*   Updated: 2024/03/26 16:41:25 by mnie             ###   ########.fr       */
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