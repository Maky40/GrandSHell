/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:16:27 by xberger           #+#    #+#             */
/*   Updated: 2023/11/24 13:51:48 by xberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h> 
# include <sys/wait.h>

void	execute(char *cmd, char **envp);
void	child_process(int *fd, char **argv, char **envp);
void	parent_process(int *fd, char **argv, char **envp);
void	pipex(char **argv, char **envp);
char	*find_path(char *cmd, char **envp);

#endif
