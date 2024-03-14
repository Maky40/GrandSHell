/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:15:38 by mnie              #+#    #+#             */
/*   Updated: 2024/03/14 10:55:11 by mnie             ###   ########.fr       */
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

typedef struct s_fd
{
	char		*str;
	t_tokens	token;
	int			last;
}	t_fd;

typedef struct s_command
{
	char 	*command;
	char	**arguments;
	t_fd	*fd;
	char	*input_file;
	char	*output_file;
	int		intput_file;
	int		output_file;
	int		heredoc_last;
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
void new_str_null(t_lexer *dup, t_expander *expander, char **ptr);
void new_str(t_lexer *dup, t_expander *expander, char **ptr);
void new_str_number(t_lexer *dup, t_expander *expander, char **ptr);
void executor(t_table *tab_cmds, t_data *data);
void	add_fd(t_command *cmd, t_lexer *lst, int i, int len);
void	set_input_output(t_command *cmd, int i, int len);
void	nb_command(t_table *tab_cmds, t_lexer **lexer);
void	free_lexer(t_lexer **lexer);
void	free_table_cmd(t_table *tab_cmd);
int		search_operators(char c);
int		verify_line(t_lexer **lexer);
t_table	*table_command(t_lexer **lexer);
#endif
