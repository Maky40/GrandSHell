/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:16:07 by xberger           #+#    #+#             */
/*   Updated: 2023/11/26 16:43:46 by xberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	child_process(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		perror("Open fd child");
		exit(EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute(argv[2], envp);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_out < 0)
	{
		perror("Open fd parent");
		exit(EXIT_FAILURE);
	}
	dup2(fd_out, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	execute(argv[3], envp);
}

void	pipex(char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	child;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	child = fork();
	if (child < 0)
	{
		perror("Fork :");
		exit(EXIT_FAILURE);
	}
	if (child == 0)
		child_process(fd, argv, envp);
	waitpid(child, &status, WNOHANG);
	parent_process(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		perror("Usage : ./pipex file1 cmd1 file2 cmd2");
		exit(EXIT_FAILURE);
	}
	pipex(argv, envp);
	return (0);
}
