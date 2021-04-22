#include "philo_two.h"

void	sleaping(t_philosoph *philosoph)
{
	sem_wait(philosoph->chat);
	printf("%zd %d is sleaping\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	sem_post(philosoph->chat);
	fn_usleep(philosoph->param.time_to_sleep);
}

void	eating(t_philosoph *philosoph)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	philosoph->timer = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	sem_wait(philosoph->chat);
	printf("%zd %d is eating\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	sem_post(philosoph->chat);
	fn_usleep(philosoph->param.time_to_eat);
}

void	thinking(t_philosoph *philosoph)
{
	sem_wait(philosoph->chat);
	printf("%zd %d is thinking\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	sem_post(philosoph->chat);
}

int	philo_life(t_philosoph	*philosoph)
{
	philosoph->wait[philosoph->i - 1] = '1';
	while (1)
		if (philosoph->wait[philosoph->i - 1] != '1')
			break ;
	sem_wait(philosoph->chat);
	printf("%zd %d has taken a fork\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	sem_post(philosoph->chat);
	eating(philosoph);
	sem_post(philosoph->prongs);
	sem_post(philosoph->prongs);
	philosoph->counter->count_prongs += 2;
	if ((int)philosoph->count_eat != -1)
	{
		philosoph->count_eat--;
		if (philosoph->count_eat == 0)
		{
			philosoph->counter->count_eat += 1;
			return (0);
		}
	}
	sleaping(philosoph);
	thinking(philosoph);
	return (1);
}

void	*cycle_of_life(void *pr)
{
	struct timeval	t1;
	t_philosoph		*philosoph;

	philosoph = (t_philosoph *)pr;
	pthread_detach(*philosoph->life);
	sem_wait(philosoph->chat);
	philosoph->counter->count_philosopher--;
	sem_post(philosoph->chat);
	while (1)
	{
		if (philosoph->counter->count_philosopher == 0)
			break ;
	}
	gettimeofday(&t1, NULL);
	philosoph->timer = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	while (1)
	{
		if ((philo_life(philosoph)) != 1)
			break ;
	}
	return (NULL);
}
