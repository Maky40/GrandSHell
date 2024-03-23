/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:18:42 by xav               #+#    #+#             */
/*   Updated: 2024/03/23 14:53:09 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int exec_open_output(t_table *tab_cmds, int i)
{
	if (tab_cmds->commands->append_last == 1)
	{
		return (open(tab_cmds->commands[i].output_file,
		O_CREAT | O_RDWR | O_APPEND, 0777));
	}
	else
	{
		return(open(tab_cmds->commands[i].output_file,
		O_CREAT | O_RDWR | O_TRUNC, 0777));
	}
}

void child_process(t_table *tab_cmds, int i, int *fd)
{
	if (tab_cmds->commands[i].input_file != NULL || tab_cmds->commands[i].output_file != NULL)
	{
		if (tab_cmds->commands[i].input_file != NULL)
		{
			tab_cmds->commands[i].in_fd = open(tab_cmds->commands[i].input_file, O_RDONLY);
			dup2(tab_cmds->commands[i].in_fd, STDIN_FILENO);
		}
		if (tab_cmds->commands[i].output_file != NULL)
		{
			tab_cmds->commands[i].out_fd = exec_open_output(tab_cmds, i);
			dup2(tab_cmds->commands[i].out_fd, STDOUT_FILENO);
		}
		else
			dup2(fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
	}
	close(fd[0]);
	close(fd[1]);
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


void execute(t_command *cmd, t_data *data)
{
	char 	*path;

	if (access(cmd->command, F_OK | X_OK) == 0)
		path = cmd->command;
	else
		path = find_path(cmd->command, data->env);
	if (!path)
		perror("Command not found");
	if (execve(path, cmd->arguments, data->env) == -1)
		return ;

}

void start_execute(t_data *data, t_table *tab_cmds, int i, t_env **env)
{
	t_env *lst;

	if (tab_cmds->commands[i].command != NULL)
	{
		if (is_builtin(tab_cmds->commands[i].command) == 0)
			built_in_execute(&tab_cmds->commands[i], data, env);
		else
			execute(&tab_cmds->commands[i], data);
	}
	lst = *env;
	while (lst->next)
		lst = lst->next;
	ft_printf("apres execution de start execute %s\n", lst->vars_add[0]);
}

void executor(t_table *tab_cmds, t_data *data, t_env **env)
{
    int i;
    int status;
    pid_t pid;
    int prev_pipe[2];
    int curr_pipe[2];

    // Initialiser le premier tube
    pipe(prev_pipe);

    for (i = 0; i < tab_cmds->num_commands; i++)
    {
        // Créer un nouveau tube pour la prochaine commande
        if (i < tab_cmds->num_commands - 1)
        {
            pipe(curr_pipe);
        }

        // Fork pour exécuter la commande
        pid = fork();
        if (pid == 0)
        {
            // Fermer l'extrémité inutilisée du tube précédent
            if (i > 0)
            {
                close(prev_pipe[1]);  // Fermer l'extrémité d'écriture du tube précédent
                dup2(prev_pipe[0], STDIN_FILENO);  // Rediriger l'entrée standard à partir du tube précédent
                close(prev_pipe[0]);  // Fermer l'extrémité de lecture du tube précédent
            }

            // Fermer l'extrémité inutilisée du tube actuel
            if (i < tab_cmds->num_commands - 1)
            {
                close(curr_pipe[0]);  // Fermer l'extrémité de lecture du tube actuel
                dup2(curr_pipe[1], STDOUT_FILENO);  // Rediriger la sortie standard vers le tube actuel
                close(curr_pipe[1]);  // Fermer l'extrémité d'écriture du tube actuel
            }

            // Rediriger les fichiers d'entrée et de sortie si nécessaire
            if (tab_cmds->commands[i].input_file != NULL)
            {
                int input_fd = open(tab_cmds->commands[i].input_file, O_RDONLY);
                if (input_fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            if (tab_cmds->commands[i].output_file != NULL)
            {
                int output_fd = open(tab_cmds->commands[i].output_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
                if (output_fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }

            // Exécuter la commande
            start_execute(data, tab_cmds, i, env);

            // Terminer le processus enfant
            exit(EXIT_SUCCESS);
        }
        else if (pid < 0)
        {
            // Gérer l'erreur de fork
            perror("fork");
            exit(EXIT_FAILURE);
        }

        // Fermer le tube précédent s'il n'est plus nécessaire
        if (i > 0)
        {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }

        // Mettre à jour prev_pipe pour le prochain itératif
        prev_pipe[0] = curr_pipe[0];
        prev_pipe[1] = curr_pipe[1];
    }

    // Attendre la fin de tous les processus enfants
    for (i = 0; i < tab_cmds->num_commands; i++)
    {
        wait(&status);
    }
}


/*
void executor(t_table *tab_cmds, t_data *data)
{
    int i;
    int status;
    pid_t pid;
    int prev_pipe[2];
    int curr_pipe[2];

    // Initialiser le premier tube
    pipe(prev_pipe);

    for (i = 0; i < tab_cmds->num_commands; i++)
    {
        // Créer un nouveau tube pour la prochaine commande
        if (i < tab_cmds->num_commands - 1)
        {
            pipe(curr_pipe);
        }

        // Fork pour exécuter la commande
        pid = fork();
        if (pid == 0)
        {
            // Fermer l'extrémité inutilisée du tube précédent
            if (i > 0)
            {
                close(prev_pipe[1]);  // Fermer l'extrémité d'écriture du tube précédent
                dup2(prev_pipe[0], STDIN_FILENO);  // Rediriger l'entrée standard à partir du tube précédent
                close(prev_pipe[0]);  // Fermer l'extrémité de lecture du tube précédent
            }

            // Fermer l'extrémité inutilisée du tube actuel
            if (i < tab_cmds->num_commands - 1)
            {
                close(curr_pipe[0]);  // Fermer l'extrémité de lecture du tube actuel
                dup2(curr_pipe[1], STDOUT_FILENO);  // Rediriger la sortie standard vers le tube actuel
                close(curr_pipe[1]);  // Fermer l'extrémité d'écriture du tube actuel
            }

            // Exécuter la commande
            start_execute(data, tab_cmds, i);

            // Terminer le processus enfant
            exit(EXIT_SUCCESS);
        }
        else if (pid < 0)
        {
            // Gérer l'erreur de fork
            perror("fork");
            exit(EXIT_FAILURE);
        }

        // Fermer le tube précédent s'il n'est plus nécessaire
        if (i > 0)
        {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }

        // Mettre à jour prev_pipe pour le prochain itératif
        prev_pipe[0] = curr_pipe[0];
        prev_pipe[1] = curr_pipe[1];
    }

    // Attendre la fin de tous les processus enfants
    for (i = 0; i < tab_cmds->num_commands; i++)
    {
        wait(&status);
    }
}*/
