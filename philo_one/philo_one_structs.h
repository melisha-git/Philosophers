#ifndef PHILO_ONE_STRUCTS_H
# define PHILO_ONE_STRUCTS_H
# include "philo_one.h"

typedef struct s_params
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_philosopher_must_eat;
	ssize_t			begin_timer;
}				t_params;
typedef struct s_counter
{
	unsigned int	counter_eat;
}	t_counter;
typedef struct s_philo
{
	unsigned int		i;
	t_counter			*count;
	pthread_mutex_t		*chat;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	unsigned long long	timer;
	t_params			param;
	pthread_t			*life;
	unsigned int		count_eat;
}	t_philosoph;
typedef struct s_global
{
	t_params		param;
	pthread_mutex_t	*prongs;
	t_philosoph		*philosoph;
	pthread_t		*life;
	pthread_mutex_t	chat;
	pthread_t		count_life;
	unsigned int	i;
}	t_global;

#endif