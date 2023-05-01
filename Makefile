NAME = philo

SRCS = ./srcs/main.c

OBJ = $(SRCS:.c=.o)
CC = gcc 
CFLAGS = -Wall -Wextra -Werror

SRCS = 	./srcs/main.c\
		./srcs/utils.c\
		./srcs/philo_action.c\
		.srcs/init_param.c

all: ${NAME}

${NAME}: ${OBJ}
		$(CC) $(SRCS) $(CFLAGS) -o $(NAME)
		@echo "making ${NAME}..."

clean:
				rm -f *~ ${OBJ}

fclean: clean
				rm -f ${NAME}
				rm -f bonus

re: fclean all


run: philo
	@./philo

push:	
	@(git add .)
	@(git commit -m "backup")
	@(git push)
	@clear