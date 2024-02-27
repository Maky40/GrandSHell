/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:15:38 by mnie              #+#    #+#             */
/*   Updated: 2024/02/27 14:09:59 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/include/libft.h"
# include "../libraries/gnl/include/get_next_line.h"
# include "../libraries/ft_printf/include/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef enum s_tokens
{
	PIPE,
	HEREDOC,
	INPUT,
	OUTPUT,
	APPEND,
	AND,
	OR,
	PARENTHESIS,
	WILDCARD,
}	t_tokens;

typedef struct s_lexer
{
	char	*str;
	t_tokens token;
	int	index;
	struct s_lexer *next;
	struct s_lexer *prev;
}	t_lexer;

typedef struct s_command
{
	char 	*command;
	char	**arguments;
	char	*input_file;
	char	*output_file;
}	t_command;

typedef struct s_data 
{
	char	*line;
	char	**env;
	int	exit_status;
}	t_data;

typedef struct s_table_command
{
	t_command *commands;
	int num_commands;
}	t_table;

char	**dup_env(char **envp);
void	free_dup_env(char **dup_env);

#endif
