/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:11:11 by mnie              #+#    #+#             */
/*   Updated: 2024/04/03 14:03:25 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_input_output(t_command *cmd, int i, int len)
{
	int	j;

	j = 0;
	cmd[i].input_file = NULL;
	cmd[i].output_file = NULL;
	if (len > 0)
	{
		while (j < len)
		{
			if (cmd[i].fd[j].token == INPUT || cmd[i].fd[j].token == OUTPUT
				|| cmd[i].fd[j].token == APPEND)
			{
				if (cmd[i].fd[j].token == INPUT)
					cmd[i].input_file = ft_strdup(cmd[i].fd[j].str);
				if (cmd[i].fd[j].token == OUTPUT)
					cmd[i].output_file = ft_strdup(cmd[i].fd[j].str);
				if (cmd[i].fd[j].token == APPEND)
					cmd[i].output_file = ft_strdup(cmd[i].fd[j].str);
			}
			j++;
		}
	}
}

void	add_fd(t_command *cmd, t_lexer *lst, int i, int len)
{
	t_lexer	*lst2;
	int		j;

	j = 0;
	lst2 = lst;
	while (j < len)
	{
		cmd[i].fd[j].str = NULL;
		cmd[i].fd[j].token = NUL;
		if (lst2 -> token == INPUT || lst2 -> token == OUTPUT
			|| lst2 -> token == HEREDOC || lst2 -> token == APPEND)
		{
			cmd[i].fd[j].last = 0;
			cmd[i].fd[j].token = lst2 -> token;
			lst2 = lst2 -> next;
			if (lst2 == NULL)
				return ;
			cmd[i].fd[j].str = ft_strdup(lst2 -> str);
			j++;
		}
		lst2 = lst2 -> next;
	}
	if (j > 0)
		cmd[i].fd[j - 1].last = 1;
}

int	is_last_fd(t_fd *fd, int j, int len)
{
	t_tokens	token;

	token = fd[j].token;
	j++;
	while (j < len)
	{
		if (token == fd[j].token)
			return (0);
		j++;
	}
	return (1);
}

void	nb_command(t_table *tab_cmds, t_lexer **lexer)
{
	int		i;
	t_lexer	*lst;

	i = 1;
	lst = *lexer;
	while (lst)
	{
		if (lst -> token == PIPE)
			i++;
		lst = lst -> next;
	}
	tab_cmds -> num_commands = i;
	return ;
}
