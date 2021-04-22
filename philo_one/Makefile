NAME= philo_one

SRC = cycle_of_life.c philo_one.c start.c utils.c working_with_params.c

CC = gcc -Wall -Werror -Wextra

HEAD = philo_one.h philo_one_structs.h

all:$(NAME)

$(NAME):$(SRC) $(HEAD)
	$(CC) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

norm:
	norminette $(SRC)
	norminette $(HEAD)

re: fclean all

PHONY: all clean fclean re