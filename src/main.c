/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:57 by mnie              #+#    #+#             */
/*   Updated: 2024/04/05 14:16:36 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal;

void	display_prompt(t_data *data)
{
	data->valid_line = 0;
	data->line = readline("minishell> ");
	if (data->line && *data->line)
		add_history(data->line);
	check_invalid_line(data);
}

void	handler_sig_cmd(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_signal = 130;
	}
}

void	handler_sig(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
	}
}

void	do_data_line_ok(t_data *data, t_lexer **lexer, t_table *tab_cmds)
{
	identify_line(data, lexer);
	check_lexer(data, lexer);
	if (data -> valid_lexer == 0)
	{
		free_lexer(lexer);
		ft_printf("bash: syntax error near unexpected token\n");
		data -> exit_status = 2;
	}
	else
	{
		tab_cmds = table_command(lexer);
		free_lexer(lexer);
		signal(SIGINT, handler_sig_cmd);
		executor(tab_cmds, data);
		free_table_cmd(tab_cmds);
	}
	free(data -> line);
	free(data -> quote_space);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_lexer	*lexer;
	t_table	*tab_cmds;

	(void)argv;
	if (argc != 1)
		return (ft_printf("Error, no argument needed\n"), 1);
	lexer = NULL;
	tab_cmds = NULL;
	data.env = dup_env(envp);
	maj_shlvl(&data, envp);
	data.exit_status = 0;
	data.exit = 0;
	while (1)
	{
		g_signal = -1;
		signal(SIGINT, handler_sig);
		signal(SIGQUIT, SIG_IGN);
		data.quote_space = NULL;
		display_prompt(&data);
		if (data.line == NULL)
			ft_exit(&data, tab_cmds);
		if (data.valid_line == 0)
			do_data_line_ok(&data, &lexer, tab_cmds);
	}
}
