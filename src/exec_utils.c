/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:37:56 by xav               #+#    #+#             */
/*   Updated: 2024/03/26 16:21:29 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_open_output(t_table *tab_cmds, int i)
{
	if (tab_cmds->commands->append_last == 1)
	{
		return (open(tab_cmds->commands[i].output_file,
				O_CREAT | O_RDWR | O_APPEND, 0777));
	}
	else
	{
		return (open(tab_cmds->commands[i].output_file,
				O_CREAT | O_RDWR | O_TRUNC, 0777));
	}
}

void	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*join_path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
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

void	execute(t_table *tab_cmds, t_data *data, t_env **env, int i)
{
	char	*path;

	if (access(tab_cmds->commands[i].command, F_OK | X_OK) == 0)
		path = tab_cmds->commands[i].command;
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
		free_builtin_process(tab_cmds, data, env);
		exit(127);
	}
}

void	start_execute(t_data *data, t_table *tab_cmds, int i, t_env **env)
{
	if (tab_cmds->commands[i].command != NULL)
	{
		if (is_builtin(tab_cmds->commands[i].command) == 0)
		{
			built_in_execute(&tab_cmds->commands[i], data, env);
			if (tab_cmds->commands[i].builtin_process == 1)
				free_builtin_process(tab_cmds, data, env);
		}
		else
			execute(tab_cmds, data, env, i);
	}
}
