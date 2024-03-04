/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:57 by mnie              #+#    #+#             */
/*   Updated: 2024/03/04 17:39:57 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	(void)argv;
	(void)envp;
	lexer = NULL;
	if (argc != 1)
		return (ft_printf("Error, no argument needed\n"),1);
	data.env = dup_env(envp);
	while (1)
	{
		do_func = 1;
		signal(SIGINT, handler_sig);
		signal(SIGSEGV, handler_sig);
		signal(SIGQUIT, SIG_IGN);
		data.line = readline("minishell> ");
		if (data.line && *data.line)
			add_history(data.line);
		identify_line(&data, &lexer);
		// free(data.line);
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
