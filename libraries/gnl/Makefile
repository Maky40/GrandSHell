NAME = gnl.a

CC			=	cc

CFILE = \
	get_next_line_utils.c get_next_line.c

CFILE_DIR		=	./src/

SRC				=	$(addprefix $(CFILE_DIR), $(CFILE))

INCLUDE_DIR		=	./include/

FLAG			=	-Wall -Wextra -Werror

INCLUDE			=	get_next_line.h

OBJ				=	$(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
