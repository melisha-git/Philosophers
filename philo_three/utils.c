#include "philo_three.h"

ssize_t	get_time(ssize_t timing)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000 + t.tv_usec / 1000) - timing);
}

void	fn_usleep(long tim)
{
	struct timeval	t1;
	ssize_t			timing;

	gettimeofday(&t1, NULL);
	timing = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	while (tim > (t1.tv_sec * 1000 + t1.tv_usec / 1000) - timing)
	{
		gettimeofday(&t1, NULL);
		usleep(100);
	}
}

void	fn_error(char *str)
{
	printf("%s", str);
	exit(0);
}

int	free_pids(int i, pid_t *pid, sem_t *chat)
{
	int	j;

	j = 0;
	sem_wait(chat);
	while (j < i)
	{
		kill(pid[j], 2);
		j++;
	}
	return (0);
}
