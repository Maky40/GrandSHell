NAME		=	minishell

CC			=	cc

FLAG		=	-Wall -Wextra -Werror -g

LIBFT_PATH	=	./libraries/libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

PRINTF_PATH	=	./libraries/ft_printf/

PRINTF_FILE	=	printf.a

PRINTF_LIB	=	$(addprefix $(PRINTF_PATH), $(PRINTF_FILE))

GNL_PATH	=	./libraries/gnl/

GNL_FILE	=	gnl.a

GNL_LIB	=	$(addprefix $(GNL_PATH), $(GNL_FILE))

C_FILE		=	main.c identification.c add_node.c quotes_utils.c check_line.c expander.c expander_utils.c executor.c table_cmd_utils.c \
				table_command.c fd_utils.c free_table_command.c executor_built_in_utils.c byebye_quotes.c env_utils.c heredoc.c builtins/export.c \
				exec_utils.c builtins/pwd.c builtins/echo.c builtins/cd.c free_utils.c  builtins/export_utils.c builtins/export_simple.c \
				builtins/export_utils2.c builtins/unset.c builtins/add_exit_env.c builtins/env.c valid_lexer.c id_utils.c

SRC_DIR		=	./src/

INC_DIR		=	./include/

SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJ			=	$(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

lib:
	@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)\n"
	@make -C $(LIBFT_PATH)
	@echo "\033[1;32mLIBFT_lib created\n"

gnl:
	@echo "\033[0;33m\nCOMPILING $(GNL_PATH)\n"
	@make -C $(GNL_PATH)
	@echo "\033[1;32mGNL_lib created\n"

printf:
	@echo "\033[0;33m\nCOMPILING $(PRINTF_PATH)\n"
	@make -C $(PRINTF_PATH)
	@echo "\033[1;32mPRINTF_lib created\n"

$(NAME): lib gnl printf $(OBJ)
	@echo "\033[0;33m\nCOMPILING minishell...\n"
	$(CC) $(OBJ) $(LIBFT_LIB) $(GNL_LIB) $(PRINTF_LIB) -lreadline -o $(NAME)
	@echo "\033[1;32m./minishell created\n"

clean:
	@echo "\033[0;31mDeleting Obj file in $(LIBFT_PATH)...\n"
	@make clean -sC $(LIBFT_PATH)
	@echo "\033[0;31mDeleting Obj file in $(GNL_PATH)...\n"
	@make clean -sC $(GNL_PATH)
	@echo "\033[0;31mDeleting Obj file in $(PRINTF_PATH)...\n"
	@make clean -sC $(PRINTF_PATH)
	@echo "\033[1;32mDone\n"
	@echo "\033[0;31mDeleting minishell object...\n"
	@rm -f $(OBJ)
	@echo "\033[1;32mDone\n"

fclean: clean
	@echo "\033[0;31mDeleting minishell executable..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(GNL_PATH)
	@make fclean -C $(PRINTF_PATH)
	@echo "\033[1;32mDone\n"

re: fclean all

.PHONY: all clean fclean re
