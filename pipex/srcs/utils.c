/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:27:16 by xberger           #+#    #+#             */
/*   Updated: 2024/02/28 09:03:53 by mnie             ###   ########.fr       */
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
	int		j;

	j = 0;

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
	while (cmds[j])
	{
		printf("%s\n", cmds[j]);
		j++;
	}
	if (execve(path, cmds, envp) == -1)
	{
		perror("Execve error");
		exit(EXIT_FAILURE);
	}
}
