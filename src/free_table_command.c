/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:45:48 by mnie              #+#    #+#             */
/*   Updated: 2024/03/11 17:36:47 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_fd(t_fd *fd)
{
	int	i;

	i = 0;
	while (fd[i].last != 1)
	{
		free(fd[i].str);
		i++;
	}
	free(fd[i].str);
	free(fd);
	fd = NULL;

}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}

void	free_commands(t_command *cmd, int i)
{
	free(cmd[i].command);
	free(cmd[i].input_file);
	free(cmd[i].output_file);
	free_fd(cmd[i].fd);
	free_args(cmd[i].arguments);
}

void	free_table_cmd(t_table *tab_cmd)
{
	int	i;

	i = 0;
	if (!tab_cmd)
		return ;
	while (i < tab_cmd -> num_commands)
	{
		free_commands(tab_cmd -> commands, i);
		i++;
	}
	free (tab_cmd);
	tab_cmd = NULL;
}