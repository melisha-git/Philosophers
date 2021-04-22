#include "philo_one.h"

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

int	fn_error(char *str)
{
	printf("%s", str);
	return (-1);
}
