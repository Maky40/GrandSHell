/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:15:38 by mnie              #+#    #+#             */
/*   Updated: 2024/02/28 13:40:12 by xav              ###   ########.fr       */
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
	COMMAND, 
	ARGS,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	EXPANSION,
}	t_tokens;

typedef struct s_lexer
{
	char	*str;
	t_tokens token;
	int	index;
	int command;
	int	args; 
	struct s_lexer *next;
	struct s_lexer *prev;
	int nb_command;
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
	int		index; 
	int	exit_status;
}	t_data;

typedef struct s_table_command
{
	t_command *commands;
	int num_commands;
}	t_table;

char	**dup_env(char **envp);
void	free_dup_env(char **dup_env);
void	identify_line(t_data *data);
char	**ft_split_command(char *str, char c);
#endif