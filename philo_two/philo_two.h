#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <pthread.h>

typedef struct s_params
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_philosopher_must_eat;
	ssize_t			begin_timer;
}				t_params;
typedef struct s_count
{
	unsigned int	count_eat;
	unsigned int	count_prongs;
	unsigned int	count_philosopher;
}	t_count;
typedef struct s_philosoph
{
	sem_t				*chat;
	char				*wait;
	sem_t				*prongs;
	t_count				*counter;
	unsigned int		i;
	unsigned long long	timer;
	unsigned int		count_eat;
	t_params			param;
	pthread_t			*life;
}	t_philosoph;
typedef struct s_glo
{
	pthread_t		count_life;
	pthread_t		waiter;
	t_params		param;
	t_philosoph		*philosoph;
	pthread_t		*life;
	unsigned int	i;
	char			*mon;
	sem_t			*chat;
	sem_t			*prongs;
	t_count			counter;
}	t_global;
void	init_params(t_params *param);
int		fn_error(char *str);
int		pars_params(t_params *param, char **argv);
void	*cycle_of_life(void *pr);
ssize_t	get_time(ssize_t timing);
void	fn_usleep(long tim);
void	*count_to_die(void *pr);
void	*cycle_waiter(void *ap);

#endif