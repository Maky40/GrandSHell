/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:40:11 by mnie              #+#    #+#             */
/*   Updated: 2024/03/15 13:56:54 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	malloc_fd(t_command *cmd, t_lexer *lst, int i)
{
	t_lexer *lst2;
	int		j;

	lst2 = lst;
	j = 0;
	if (lst2 == NULL)
	{
		cmd[i].fd = NULL;
		return (0);
	}
	if (lst2 -> token == COMMANDE)
		lst2 = lst2 -> next;
	while (lst2 && lst2 -> token != COMMANDE)
	{
		if (lst2 -> token == FD)
			j++;
		lst2 = lst2 -> next;
	}
	if (j > 0)
		cmd[i].fd = malloc(sizeof(t_fd) * j);
	return (j);

}

void	add_input_output(t_command *cmd, t_lexer *lst, int i)
{
	int		len;

	len = malloc_fd(cmd, lst, i);
	if (len == 0)
	{
		cmd[i].no_fd = 1;
		cmd[i].fd = NULL;
		cmd[i].input_file = NULL;
		cmd[i].output_file = NULL;
		return ;
	}
	else	
		cmd[i].no_fd = 0;
	add_fd(cmd, lst, i, len);
	set_input_output(cmd, i, len);
}

void	add_args(t_command *cmd, t_lexer *lst, int i)
{
	int		j;
	t_lexer	*lst2;

	j = 0;
	lst2 = lst -> next;
	while (lst2 && lst2 -> token != COMMANDE)
	{
		if (lst2 -> token == ARG)
			j++;
		lst2 = lst2 -> next;
	}
	cmd[i].arguments = malloc(sizeof(char *) * (j + 1));
	cmd[i].arguments[j] = NULL;
	j = 0;
	lst2 = lst -> next;
	while (lst2 && lst2 -> token != COMMANDE)
	{
		if (lst2 -> token == ARG)
		{
			cmd[i].arguments[j] = ft_strdup(lst2 -> str);
			j++;
		}
		lst2 = lst2 -> next;
	}
}
void	add_commands(t_table *tab_cmds, t_lexer **lexer)
{
	int		i;
	t_lexer	*lst;

	i = 0;
	lst = *lexer;
	while (i < tab_cmds -> num_commands)
	{
		if (lst -> token == COMMANDE)
			tab_cmds -> commands[i].command = ft_strdup(lst -> str);
		else
			tab_cmds -> commands[i].command = NULL;
		add_args(tab_cmds -> commands, lst, i);
		add_input_output(tab_cmds -> commands, lst, i);
		i++;
		lst = lst -> next;
		while (lst && lst -> token != PIPE)
			lst = lst -> next;
		if (lst == NULL)
			return ;
		if (lst -> token == PIPE)
			lst = lst -> next;
	}
}

t_table	*table_command(t_lexer **lexer)
{
	t_table	*tab_cmds;
	int		i;
	int		j;

	i = 0;
	tab_cmds = malloc(sizeof(t_table));
	nb_command(tab_cmds, lexer);
	if (tab_cmds -> num_commands > 0)
	{
		tab_cmds -> commands = malloc(sizeof(t_command) * (tab_cmds -> num_commands));
		add_commands(tab_cmds, lexer);
	}
	while (i < tab_cmds -> num_commands)
	{
		j = 0;
		ft_printf("la commande %d est : %s\n", i, tab_cmds -> commands[i].command);
		while (tab_cmds -> commands[i].arguments[j])
		{
			ft_printf("argument %d est : %s\n", j, tab_cmds -> commands[i].arguments[j]);
			j++;
		}
		ft_printf("argument %d est : %s\n", j, tab_cmds -> commands[i].arguments[j]);
		j = 0;
		if (tab_cmds -> commands[i].fd)
		{
			while (tab_cmds -> commands[i].fd[j].last != 1)
			{
				ft_printf("Pour fd = %d :\nToken = %d\nSTR = %s\n\n", j, tab_cmds -> commands[i].fd[j].token, tab_cmds -> commands[i].fd[j].str);
				j++;
			}
			ft_printf("Pour fd = %d :\nToken = %d\nSTR = %s\n\n", j, tab_cmds -> commands[i].fd[j].token, tab_cmds -> commands[i].fd[j].str);
		}
		ft_printf("INPUT FILE = %s, OUTPUT FILE = %s\n", tab_cmds -> commands[i].input_file, tab_cmds -> commands[i].output_file);
		i++;
	}
	return (tab_cmds);
	// ft_printf("la commande est : %s\n", tab_cmds -> commands[1].command);
	
}
