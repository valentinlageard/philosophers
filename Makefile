NAME		=	philo
SRC		=	philosophers.c \
			death.c \
			fork.c \
			philosopher_routine.c \
			utils.c

OBJS		=	$(SRC:.c=.o)

FLAGS		=	-Wall -Wextra -Werror
LIBS		=	-lpthread
CC			=	gcc $(FLAGS)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

%.o: %.cpp
			$(CC) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:
			make clean
			rm -f $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re
