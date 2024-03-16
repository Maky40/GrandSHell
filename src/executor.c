/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:18:42 by xav               #+#    #+#             */
/*   Updated: 2024/03/16 12:21:08 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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

void init_pipe(t_table *tab_cmds, t_data *data, int i)
{
	int fd[2];
	int status;
	int pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		printf("Je suis processus enfant\n");
		start_execute(data, tab_cmds, i, fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fd[0]);
		close(fd[1]);
	}
}
int check_command(char *str, char *cmd)
{
	int i; 

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i++; 
		if (str[i] != cmd[i])
			return (1);
		i++;
	}
	return (0);
}

void execute(t_command *cmd, t_data *data)
{
	char *path; 
	
	path = find_path(cmd->command, data->env);
	if (!path)
	{
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	printf("Je suis avant execve\n");
	if (execve(path, cmd->arguments, data->env) == -1)
	{
		perror("Execve error");
		exit(EXIT_FAILURE);
	}
	
}

void	built_in_execute(t_command *cmd, t_data *data)
{
	(void)data;
	if (check_command(cmd->command, "echo") == 0)
		printf("echo\n");
	else if (check_command(cmd->command, "unset") == 0)
		printf("unset\n");
	else if (check_command(cmd->command, "cd") == 0)
		printf("cd\n");
	else if (check_command(cmd->command, "exit") == 0)
		printf("exit\n");
	else if (check_command(cmd->command, "pwd") == 0)
		printf("pwd\n");
	else if (check_command(cmd->command, "env") == 0)
		printf("env\n");
	else if (check_command(cmd->command, "export") == 0)
		printf("export\n");
}

int	is_builtin(char *cmd)
{
	int ret; 

	ret = 1;
	if (check_command(cmd, "echo") == 0)
		ret = 0;
	else if (check_command(cmd, "unset") == 0)
		ret = 0;
	else if (check_command(cmd, "cd") == 0)
		ret = 0;
	else if (check_command(cmd, "exit") == 0)
		ret = 0;
	else if (check_command(cmd, "pwd") == 0)
		ret = 0;
	else if (check_command(cmd, "env") == 0)
		ret = 0;
	else if (check_command(cmd, "export") == 0)
		ret = 0;
	return (ret);
}

void start_execute(t_data *data, t_table *tab_cmds, int i , int *fd)
{
	
	
    if (tab_cmds->commands[i].input_file == NULL)
        dup2(fd[0], STDIN_FILENO);
    else
        dup2(fd[0], tab_cmds->commands[i].input_file_fd);
    if (tab_cmds->commands[i].output_file == NULL)
        dup2(fd[1], STDOUT_FILENO);
    else
        dup2(fd[1], tab_cmds->commands[i].output_file_fd);

    close(fd[0]);
    close(fd[1]);
    if (tab_cmds->commands[i].command != NULL)
    {
        if (is_builtin(tab_cmds->commands[i].command) == 0)
            built_in_execute(&tab_cmds->commands[i], data);
        else
            execute(&tab_cmds->commands[i], data);
    }
}

void executor(t_table *tab_cmds, t_data *data)
{
	int i;
	
	i = 0;
	while (i < tab_cmds->num_commands)
	{
		if (open_fd(&tab_cmds->commands[i], data) == 0)
			init_pipe(tab_cmds, data, i);
		i++;
	}
}


