NAME= philo_three

SRC = philo_three.c utils.c working_with_params.c cycle_of_life.c count_to_die.c

CC = gcc -Wall -Werror -Wextra

HEAD = philo_three.h

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