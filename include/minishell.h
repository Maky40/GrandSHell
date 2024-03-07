/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:15:38 by mnie              #+#    #+#             */
/*   Updated: 2024/03/07 12:28:31 by xav              ###   ########.fr       */
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
# include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

//int	do_func = 1;

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
	ARG,
	COMMANDE,
	FD,
	NUL,
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
	int		exit_status;
	int		index_line;
	int		*quote_space;
	int	valid_line;
}	t_data;

typedef struct s_expander
{
	char	*start;
	char	*end;
	char	*value;
	char	*name;
	size_t	len;
}	t_expander;

typedef struct s_table_command
{
	t_command *commands;
	int num_commands;
}	t_table;

char	**dup_env(char **envp);
void	free_dup_env(char **dup_env);
void	identify_line(t_data *data, t_lexer **lexer);
void	str_quotes_operators(t_data *data, int j, int i, t_lexer **lexer);
void	add_node(t_data *data, int i, int j, t_lexer **lexer);
void	process_single_quotes(t_data *data, int *j, int i, t_lexer **lexer);
void	process_double_quotes(t_data *data, int *j, int i, t_lexer **lexer);
void	check_invalid_line(t_data *data);
void	expander(t_data *data, t_lexer **lexer);
int		search_operators(char c);
#endif
