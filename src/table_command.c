/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:40:11 by mnie              #+#    #+#             */
/*   Updated: 2024/03/09 10:58:51 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	add_fd(t_command cmd, t_lexer *lst)
{
	t_lexer *lst2;
	int		i;

	cmd.fd = malloc_fd(lst);
	i = 0;
	lst2 = lst;
	while (lst2 && lst2 -> token == INPUT && lst2 -> token == OUTPUT \
	&& lst2 -> token == FD)
	{
		if (lst2 -> token == FD)
		{
			cmd.fd[i].last = 0;
			cmd.fd[i].token = lst2 -> prev -> token;
			cmd.fd[i].str = ft_strdup(lst2 -> str);
			i++;
		}
		lst2 = lst2 -> next;
	}
	cmd.fd[i].last = 1;
}

t_lexer	*add_input_output(t_command *cmd, t_lexer *lst, int i)
{
	int	len;
	int	j;

	j = 0;
	if (lst -> token == INPUT || lst -> token == OUTPUT)
	{
		add_fd(cmd[i], lst);
		len = len_fd(cmd[i].fd);
		while (j < len)
		{
			if ((cmd[i].fd[j].token == INPUT || cmd[i].fd[j].token == OUTPUT) \
			&& is_last_fd(cmd[i].fd, j, len) == 1)
			{
				if (cmd[i].fd[j].token == INPUT)
					cmd[i].input_file = ft_strdup(cmd[i].fd[j].str);
				else
					cmd[i].output_file = ft_strdup(cmd[i].fd[j].str);
			}
			j++;
		}
		lst = lst -> next;
	}
	return (lst);
}
t_lexer	*add_args(char **args, t_lexer *lst)
{
	int		i;
	t_lexer	*lst2;

	i = 0;
	lst2 = lst;
	while (lst2 && lst2 -> token == ARG)
	{
		i++;
		lst2 = lst2 -> next;
	}
	args = malloc(sizeof(char *) * ( i + 1));
	args[i] = NULL;
	i = 0;
	while (args[i])
	{
		args[i] = ft_strdup(lst -> str);
		lst = lst -> next;
	}
	return (lst);
}
void	add_commands(t_table *tab_cmds, t_lexer **lexer)
{
	int		i;
	t_lexer	*lst;

	i = 0;
	lst = *lexer;
	tab_cmds -> commands[i].pipe_bef = 0;
	while (i < tab_cmds -> num_commands)
	{
		if (lst -> token == PIPE)
			tab_cmds -> commands[i].pipe_bef = 1;
		else
			tab_cmds -> commands[i].pipe_bef = 0;
		if (lst -> token == COMMANDE)
		{
			tab_cmds -> commands[i].command = ft_strdup(lst -> str);
			lst = lst -> next;
			lst = add_args(tab_cmds -> commands[i].arguments, lst);
		}
		lst = add_input_output(tab_cmds -> commands, lst, i);
		i++;
	}
}

void	table_command(t_lexer **lexer)
{
	t_table	*tab_cmds;

	tab_cmds = malloc(sizeof(t_table));
	nb_command(tab_cmds, lexer);
	if (tab_cmds -> num_commands > 0)
	{
		tab_cmds -> commands = malloc(sizeof(t_command) * (tab_cmds -> num_commands));
		add_commands(tab_cmds, lexer);
	}
	ft_printf("%s\n", tab_cmds -> commands[0].command);
}