/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:57 by mnie              #+#    #+#             */
/*   Updated: 2024/03/26 17:41:16 by mnie             ###   ########.fr       */
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

void	handler_sig(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\nminishell> ");
		return ;
	}
	if (signal == SIGSEGV)
	{
		// free_all();
		exit (0);
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
	if (argc != 1)
		return (ft_printf("Error, no argument needed\n"),1);
	data.env = dup_env(envp);
	data.exit_status = 0;
	env = NULL;
	env_init(&env, envp);
	while (1)
	{
		//do_func = 1;
		signal(SIGINT, handler_sig);
		signal(SIGSEGV, handler_sig);
		signal(SIGQUIT, SIG_IGN);
		display_prompt(&data);
		if (data.valid_line == 0)
		{
			identify_line(&data, &lexer);
			tab_cmds = table_command(&lexer);
			free_lexer(&lexer);
			executor(tab_cmds, &data, &env);
			free_table_cmd(tab_cmds);
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
