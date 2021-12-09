SRCS = main.c\
		init.c\
		utils.c\
		threads.c\
		actions.c\
		routines.c\
		routine_checks.c\
		ft_usleep.c

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = clang

CFLAGS = -Wall -Wextra -Werror -Iincludes -g3

.c.o :
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${CC} -o ${NAME} ${OBJS} -lpthread

all:	${NAME}

clean :
		rm -rf ${OBJS}

fclean:	clean
		rm -rf ${NAME}

re:		fclean all


.PHONY: all clean fclean re
