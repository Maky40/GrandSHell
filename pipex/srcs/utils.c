/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:27:16 by xberger           #+#    #+#             */
/*   Updated: 2023/11/26 15:11:57 by xberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*join_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		join_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(join_path, cmd);
		free(join_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute(char *cmd, char **envp)
{
	char	**cmds;
	char	*path;
	int		i;

	i = -1;
	cmds = ft_split(cmd, ' ');
	path = find_path(cmds[0], envp);
	if (!path || !cmds)
	{
		while (cmds[++i])
			free(cmds[i]);
		free(cmds);
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmds, envp) == -1)
	{
		perror("Execve error");
		exit(EXIT_FAILURE);
	}
}
