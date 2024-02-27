NAME = printf.a

CC = cc

CFILE = ft_printf.c \
	ft_tools.c \
	ft_lens.c

CFILE_DIR		=	./src/

SRC				=	$(addprefix $(CFILE_DIR), $(CFILE))

INCLUDE_DIR		=	./include/

FLAG			=	-Wall -Wextra -Werror

INCLUDE			=	ft_printf.h

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
