/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:40:11 by mnie              #+#    #+#             */
/*   Updated: 2024/03/05 17:00:12 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*add_input_output(t_command *cmd, t_lexer *lst, int i)
{
	if (lst -> token == INPUT || lst -> token == OUTPUT)
	{
		if (lst -> token == INPUT)
		{
			lst = lst -> next;
			if (lst -> token != FD)
				ft_error();
			cmd[i].input_file = ft_strdup(lst -> str);
		}
		else if (lst -> token == OUTPUT)
		{
			lst = lst -> next;
			if (lst -> token != FD)
				ft_error();
			cmd[i].output_file = ft_strdup(lst -> str);
		}
		lst = lst -> next;
		if (lst -> token == FD)
			ft_error();
	}
	return (lst);
}
t_lexer	*add_args(char **args, t_lexer *lst)
{
	int		i;
	t_lexer	*lst2;

	i = 0;
	lst2 = lst;
	while (lst2 -> token == ARG)
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
	int		j;
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
			j = 0;
			tab_cmds -> commands[i].command = ft_strdup(lst -> str);
			lst = lst -> next;
			lst = add_args(tab_cmds -> commands[i].arguments, lst);
		}
		lst = add_input_output(tab_cmds -> commands, lst, i);
		i++;
	}
}
void	nb_command(t_table *tab_cmds, t_lexer **lexer)
{
	int		i;
	t_lexer	*lst;

	i = 0;
	lst = *lexer;
	while(lst)
	{
		if (lst -> token == COMMANDE)
			i++;
		lst = lst -> next;
	}
	tab_cmds -> num_commands = i;
	return ;
}

void	table_command(t_lexer **lexer, t_data *data)
{
	t_table	*tab_cmds;

	tab_cmds = malloc(sizeof(t_table));
	nb_command(tab_cmds, lexer);
	tab_cmds -> commands = malloc(sizeof(t_command) * (tab_cmds -> num_commands));
	add_commands(tab_cmds, lexer);
}