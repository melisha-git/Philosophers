#include "philo_one.h"

void	thinking(t_philosoph *philosoph)
{
	pthread_mutex_lock(philosoph->chat);
	printf("%zd %d is thinking\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	pthread_mutex_unlock(philosoph->chat);
}

void	sleaping(t_philosoph *philosoph)
{
	fn_usleep(philosoph->param.time_to_sleep);
	pthread_mutex_lock(philosoph->chat);
	printf("%zd %d is sleeping\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	pthread_mutex_unlock(philosoph->chat);
}

void	eating(t_philosoph *philosoph)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	philosoph->timer = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	pthread_mutex_lock(philosoph->chat);
	printf("%zd %d is eating\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	pthread_mutex_unlock(philosoph->chat);
	fn_usleep(philosoph->param.time_to_eat);
}

int	philo_life(t_philosoph	*philosoph)
{
	pthread_mutex_lock(philosoph->left);
	pthread_mutex_lock(philosoph->right);
	pthread_mutex_lock(philosoph->chat);
	printf("%zd %d has taken a fork\n", \
	get_time(philosoph->param.begin_timer), philosoph->i);
	pthread_mutex_unlock(philosoph->chat);
	eating(philosoph);
	pthread_mutex_unlock(philosoph->left);
	pthread_mutex_unlock(philosoph->right);
	if ((int)philosoph->count_eat != -1)
	{
		philosoph->count_eat--;
		if (philosoph->count_eat == 0)
		{
			philosoph->count->counter_eat += 1;
			return (0);
		}
	}
	sleaping(philosoph);
	thinking(philosoph);
	return (1);
}

void	*cycle_of_life(void *param)
{
	struct timeval	t1;
	t_philosoph		*philosoph;

	philosoph = (t_philosoph *)param;
	pthread_detach(*philosoph->life);
	if (philosoph->i % 2 == 0)
		usleep(200);
	gettimeofday(&t1, NULL);
	philosoph->timer = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	while (1)
		if (!(philo_life(philosoph)))
			break ;
	return (NULL);
}
