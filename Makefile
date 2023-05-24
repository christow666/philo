NAME = philo

SRCS = ./srcs/main.c

OBJ = $(SRCS:.c=.o)
CC = gcc 
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g -pthread

SRCS = 	./srcs/main.c\
		./srcs/utils_1.c\
		./srcs/utils_2.c\
		./srcs/philo_action.c\
		./srcs/init_param.c

all: ${NAME}

${NAME}: ${OBJ}
		$(CC) $(SRCS) $(CFLAGS) -o $(NAME)
		@echo "making ${NAME}..."

clean:
				rm -f *~ ${OBJ}

fclean: clean
				rm -f ${NAME}

re: fclean all


run: philo
	@./philo

push:	
	@(git add .)
	@(git commit -m "backup")
	@(git push)
	@clear