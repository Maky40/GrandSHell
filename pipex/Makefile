SRCS = srcs/pipex.c srcs/ft_strnstr.c srcs/utils.c srcs/ft_split.c srcs/ft_strjoin.c srcs/ft_strlen.c

OBJS = ${SRCS:.c=.o}


CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f


NAME = pipex

INC_DIR = includes
.c.o: libft.h pipex.h
	${CC} ${CFLAGS} -I${INC_DIR} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all: ${NAME}


clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
