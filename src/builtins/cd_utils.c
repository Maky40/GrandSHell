/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:53:26 by xav               #+#    #+#             */
/*   Updated: 2024/04/04 10:54:05 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*new_oldpwd(char **env, int pos_pwd)
{
	char	*pwd;
	char	*oldpwd;
	char	*new_str;

	pwd = ft_strdup(env[pos_pwd]);
	oldpwd = malloc(sizeof(char) * 4);
	oldpwd[0] = 'O';
	oldpwd[1] = 'L';
	oldpwd[2] = 'D';
	oldpwd[3] = '\0';
	new_str = ft_spe_strjoin(oldpwd, pwd);
	free(oldpwd);
	return (new_str);
}

char	*new_pwd(char *pwd, char *cwd)
{
	char	*str;

	free(pwd);
	pwd = malloc(sizeof(char) * 5);
	pwd[0] = 'P';
	pwd[1] = 'W';
	pwd[2] = 'D';
	pwd[3] = '=';
	pwd[4] = '\0';
	str = ft_spe_strjoin(pwd, cwd);
	free(pwd);
	return (str);
}
