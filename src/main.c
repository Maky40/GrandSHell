/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:57 by mnie              #+#    #+#             */
/*   Updated: 2024/02/26 11:56:07 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (ft_printf("Error, no argument needed\n"),1);
	while (1)
	{
		data.line = readline("minishell> ");
		if (data.line && *data.line)
			add_history(data.line);
		free(data.line);
	}
}
