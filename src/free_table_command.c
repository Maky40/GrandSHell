/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:45:48 by mnie              #+#    #+#             */
/*   Updated: 2024/03/15 12:56:59 by xav              ###   ########.fr       */
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
	if (cmd[i].command != NULL)
	{
		printf("Je suis free command\n");
		free(cmd[i].command);
	}
	if (cmd[i].input_file != NULL)
	{
		printf("Je suis free input\n");
		free(cmd[i].input_file);
	}
	if (cmd[i].output_file != NULL)
	{
		printf("Je suis free output\n");
		free(cmd[i].output_file);
	}
	if (cmd[i].fd != NULL)
	{
		printf("je suis free fd\n");
		free_fd(cmd[i].fd);
	}
	if (cmd[i].arguments != NULL)
	{
		printf("Je suis free arg\n");
		free_args(cmd[i].arguments);
	}
}

void	free_table_cmd(t_table *tab_cmd)
{
	int	i;
	printf("Je suis free table\n");
	i = 0;
	if (!tab_cmd)
		return ;
	while (i < tab_cmd -> num_commands)
	{
		free_commands(tab_cmd -> commands, i);
		i++;
	}
	free(tab_cmd->commands);
	free (tab_cmd);
	tab_cmd = NULL;
}