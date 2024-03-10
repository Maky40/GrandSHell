/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:40:11 by mnie              #+#    #+#             */
/*   Updated: 2024/03/10 21:21:00 by mnie             ###   ########.fr       */
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
		return (0);
	if (lst2 -> token == COMMANDE)
		lst2 = lst2 -> next;
	while (lst2 && lst2 -> token != COMMANDE)
	{
		if (lst2 -> token == FD)
			j++;
		lst2 = lst2 -> next;
	}
	cmd[i].fd = malloc(sizeof(t_fd) * j);
	return (j);

}

void	add_input_output(t_command *cmd, t_lexer *lst, int i)
{
	int		j;
	int		len;
	t_lexer *lst2;

	j = 0;
	lst2 = lst;
	len = malloc_fd(cmd, lst, i);
	while (j < len)
	{
		if (lst2 -> token == INPUT || lst2 -> token == OUTPUT || lst2 -> token == HEREDOC || lst2 -> token == APPEND)
		{
			cmd[i].fd[j].last = 0;
			cmd[i].fd[j].token = lst2 -> token;
			lst2 = lst2 -> next;
			if (lst2 == NULL)
				return ;
			cmd[i].fd[j].str = ft_strdup(lst2 -> str);
			j++;
		}
		if (lst2 == NULL)
			break ;
		lst2 = lst2 -> next;
	}

	if (j > 0)
		cmd[i].fd[j - 1].last = 1;
}
t_lexer	*add_args(char **args, t_lexer *lst)
{
	int		i;
	t_lexer	*lst2;

	i = 0;
	lst2 = lst;
	while (lst2 && lst2 -> token != COMMANDE)
	{
		if (lst2 -> token == ARG)
			i++;
		lst2 = lst2 -> next;
	}
	args = malloc(sizeof(char *) * ( i + 1));
	args[i] = NULL;
	i = 0;
	while (args[i])
	{
		if (lst -> token == ARG)
		{
			args[i] = ft_strdup(lst -> str);
			i++;
		}
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
	while (i < tab_cmds -> num_commands)
	{
		if (lst -> token == COMMANDE)
			tab_cmds -> commands[i].command = lst -> str;
		add_args(tab_cmds -> commands[i].arguments, lst);
		add_input_output(tab_cmds -> commands, lst, i);
		lst = lst -> next;
		while (lst && lst -> token != COMMANDE)
			lst = lst -> next;
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
	ft_printf("la commande est : %s\n", tab_cmds -> commands[0].command);
	ft_printf("la commande est : %s\n", tab_cmds -> commands[1].command);
}