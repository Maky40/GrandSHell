/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:15:38 by mnie              #+#    #+#             */
/*   Updated: 2024/04/02 23:34:17 by mnie             ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

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
	int	in_dq;
	int	in_sq;
	struct s_lexer *next;
	struct s_lexer *prev;
}	t_lexer;

typedef struct s_fd
{
	char		*str;
	t_tokens	token;
	int			last;
	int		heredoc_last;
}	t_fd;

typedef struct s_command
{
	char 	*command;
	char	**arguments;
	t_fd	*fd;
	char	*input_file;
	char	*output_file;
	int		in_fd;
	int		out_fd;
	int		no_fd;
	int		append_last;
	int		builtin_process;
}	t_command;

typedef struct s_data
{
	char	*line;
	char	**env;
	int		exit_status;
	int		index_line;
	int		*quote_space;
	int		valid_line;
	int		valid_lexer;
	int prev_pipe[2];
    int curr_pipe[2];
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
char	*ft_strdup_mshell(char *s);
char	*get_env_value(char **envp, char *var_name);
void	free_dup_env(char **dup_env);
void	identify_line(t_data *data, t_lexer **lexer);
void	str_quotes_operators(t_data *data, int j, int i, t_lexer **lexer);
void	add_node(t_data *data, int i, int j, t_lexer **lexer);
void	process_single_quotes(t_data *data, int *j, int i, t_lexer **lexer);
void	process_double_quotes(t_data *data, int *j, int i, t_lexer **lexer);
void	check_invalid_line(t_data *data);
void	expander(t_data *data, t_lexer **lexer);
void 	new_str_null(t_lexer *dup, t_expander *expander, char **ptr);
void 	new_str(t_lexer *dup, t_expander *expander, char **ptr);
void 	new_str_number(t_lexer *dup, t_expander *expander, char **ptr);
void 	executor(t_table *tab_cmds, t_data *data);
void	add_fd(t_command *cmd, t_lexer *lst, int i, int len);
void	set_input_output(t_command *cmd, int i, int len);
void	nb_command(t_table *tab_cmds, t_lexer **lexer);
void	free_lexer(t_lexer **lexer);
void	free_table_cmd(t_table *tab_cmd);
void	heredoc_tmp_fd(t_command *cmd, int i);
int		search_operators(char c);
int		verify_line(t_lexer **lexer);
int		check_command(char *str, char *cmd);
void 	start_execute(t_data *data, t_table *tab_cmds, int i);
void	free_table_cmd(t_table *tab_cmd);
void	free_data(t_data *data);
void	built_in_execute(t_table *tab_cmds, t_data *data, int i);
void 	purge_quotes(t_data *data, t_lexer **lexer);
void	builtin_pwd(t_command *cmd, t_data *data);
void 	builtin_cd(t_command *cmd, t_data *data);
void	builtin_echo(t_command *cmd, t_data *data);
void	free_builtin_process(t_table *tab_cmds, t_data *data);
void	free_commands(t_command *cmd, int i);
void	free_data_end(t_data *data);
int		search_operators(char c);
int		is_builtin(char *cmd);
int 	open_fd(t_command *command);
int 	exec_open_output(t_table *tab_cmds, int i);
int 	check_command(char *str, char *cmd);
int		single_process(char *cmd);
t_table	*table_command(t_lexer **lexer);
void	env_init(char **envp);
char	before_equal(char *str);
char	*ft_dup_var(char *str);
void	do_export(t_command *cmd, t_data *data);
void	do_unset(t_command *cmd, t_data *data);
void	find_and_remove(char **env, char *arguments);
char	before_equal(char *str);
int		search_variable(char **tab, char *variable);
int		find_equal(char *str);
char	*variable_without_equal(char *str);
char	*variable_without_plus_equal(char *str);
char	*variable_without_plus(char *str);
char	*add_variable(char **tab, char *str, int pos);
void	export_simple(char **tab);
int		ft_error_export(char *str);
void	ft_error_export2(char *str, t_data *data);
void	ft_exit(t_data *data, t_table *cmd);
void	print_env(t_command *cmd, t_data *data);
void	check_lexer(t_data *data, t_lexer **lexer);
int		ft_error_while(char *str);
#endif
