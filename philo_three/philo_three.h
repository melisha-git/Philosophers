#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_param
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_philosopher_must_eat;
	ssize_t			begin_timer;
}	t_params;
typedef struct s_philosoph
{
	sem_t				*chat;
	sem_t				*prongs;
	unsigned int		i;
	t_params			param;
	unsigned long long	timer;
	pid_t				*pid;
	unsigned int		count_eat;
}	t_philosoph;
typedef struct s_gl
{
	sem_t			*chat;
	pid_t			*pid;
	pthread_t		*life;
	pthread_t		craken;
	t_params		param;
	sem_t			*prongs;
	t_philosoph		*philosoph;
	unsigned int	i;
	int				status;
}	t_global;
void			init_params(t_params *param);
int				pars_params(t_params *param, char **argv);
int				validation_params(t_params *param);
unsigned int	fill_params(char *str);
void			fn_error(char *str);
ssize_t			get_time(ssize_t timing);
void			fn_usleep(long tim);
void			fn_error(char *str);
int				free_pids(int i, pid_t *pid, sem_t *chat);
void			*cycle_of_life(void *ap);
int				philo_life(t_philosoph *philosoph);
void			sleaping(t_philosoph *philosoph);
void			thinking(t_philosoph *philosoph);
void			eating(t_philosoph *philosoph);
void			*count_to_die(void *ap);
#endif