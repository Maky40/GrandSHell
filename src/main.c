/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:57 by mnie              #+#    #+#             */
/*   Updated: 2024/04/01 14:36:24 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void display_prompt (t_data *data)
{
	data->valid_line = 0;
	data->line = readline("minishell> ");
	if (data->line && *data->line)
		add_history(data->line);
	check_invalid_line(data);
}

void handler_sigchld(int signal) 
{
    int status;

	(void)signal;
    waitpid(-1, &status, WNOHANG); 
}

void	handler_sig(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_lexer	*lexer;
	t_table	*tab_cmds;
	t_env	*env;

	(void)argv;
	lexer = NULL;
	tab_cmds = NULL;
	if (argc != 1)
		return (ft_printf("Error, no argument needed\n"),1);
	data.env = dup_env(envp);
	data.exit_status = 0;
	env = NULL;
	env_init(&env, envp);
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, handler_sigchld);
	while (1)
	{

		data.quote_space = NULL;
		display_prompt(&data);
		if (data.line == NULL)
			ft_exit(&env, &data, tab_cmds);
		if (data.valid_line == 0)
		{
			identify_line(&data, &lexer);
			check_lexer(&data, &lexer);
			if (data.valid_lexer == 0)
			{
				free_lexer(&lexer);
				ft_printf("bash: syntax error near unexpected token\n");
				data.exit_status = 2;
			}
			else
			{
				tab_cmds = table_command(&lexer);
				free_lexer(&lexer);
				executor(tab_cmds, &data, &env);
				free_table_cmd(tab_cmds);
			}
			free(data.line);
			free(data.quote_space);
		}
	}
}
//int main(int argc, char **argv, char **envp)
//{
//	char	**env;
//	int		i;
//
//	(void) argc;
//	(void) argv;
//	env = dup_env(envp);
//	i = 0;
//	while (env[i])
//	{
//		ft_printf("%s\n", env[i]);
//		i++;
//	}
//	return (0);
//}
