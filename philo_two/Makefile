NAME= philo_two

SRC = count_to_die.c cycle_of_life.c cycle_waiter.c philo_two.c utils.c working_with_params.c

CC = gcc -Wall -Werror -Wextra

HEAD = philo_two.h

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