#include "philo_three.h"

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

void	sleaping(t_philosoph *philosoph)
{
	sem_wait(philosoph->chat);
	printf("%zd %d is sleaping\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	sem_post(philosoph->chat);
	fn_usleep(philosoph->param.time_to_eat);
}

int	philo_life(t_philosoph *philosoph)
{
	sem_wait(philosoph->prongs);
	sem_wait(philosoph->chat);
	printf("%zd %d has taken a fork\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	sem_post(philosoph->chat);
	sem_wait(philosoph->prongs);
	sem_wait(philosoph->chat);
	printf("%zd %d has taken a fork\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	sem_post(philosoph->chat);
	eating(philosoph);
	sem_post(philosoph->prongs);
	sem_post(philosoph->prongs);
	if ((int)philosoph->count_eat != -1)
	{
		philosoph->count_eat--;
		if (philosoph->count_eat == 0)
			exit(0);
	}
	sleaping(philosoph);
	thinking(philosoph);
	return (1);
}

void	*cycle_of_life(void *ap)
{
	struct timeval	t1;
	t_philosoph		*philosoph;

	philosoph = (t_philosoph *)ap;
	if (philosoph->i % 2 == 0)
		usleep(200);
	gettimeofday(&t1, NULL);
	philosoph->timer = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	while (1)
	{
		if ((philo_life(philosoph)) == 0)
			break ;
	}
	return (NULL);
}
