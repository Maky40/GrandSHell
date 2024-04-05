/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:37:56 by xav               #+#    #+#             */
/*   Updated: 2024/04/05 14:25:39 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_command_path(char *cmd, char **paths)
{
	char	*join_path;
	char	*path;
	int		i;

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
	return (NULL);
}

void	free_paths(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

void	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	int		bool;

	i = -1;
	bool = 0;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH", 4) != NULL)
		{
			bool = 1;
			break ;
		}
	}
	if (bool == 1)
	{
		paths = ft_split(env[i] + 5, ':');
		path = find_command_path(cmd, paths);
		free_paths(paths);
		return (path);
	}
	else
		path = NULL;
	return (path);
}

void	execute(t_table *tab_cmds, t_data *data, int i)
{
	char		*path;
	struct stat	info;

	if (access(tab_cmds->commands[i].command, F_OK | X_OK) == 0)
	{
		if (stat(tab_cmds->commands[i].command, &info) == 0
			&& !S_ISDIR(info.st_mode))
			path = tab_cmds->commands[i].command;
		else
			path = NULL;
	}
	else
		path = find_path(tab_cmds->commands[i].command, data->env);
	if (!path)
	{
		path = ft_strdup("/does_not_exist");
	}
	if (execve(path, tab_cmds->commands[i].arguments, data->env) == -1)
	{
		perror("Command not found");
		free(path);
		free_builtin_process(tab_cmds, data);
		exit(127);
	}
}

void	start_execute(t_data *data, t_table *tab_cmds, int i)
{
	if (tab_cmds->commands[i].command != NULL)
	{
		if (is_builtin(tab_cmds->commands[i].command) == 0)
		{
			built_in_execute(tab_cmds, data, i);
			if (tab_cmds->commands[i].builtin_process == 1)
				free_builtin_process(tab_cmds, data);
		}
		else
			execute(tab_cmds, data, i);
	}
}
