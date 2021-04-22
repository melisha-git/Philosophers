#include "philo_three.h"

void	*count_to_die(void *ap)
{
	struct timeval	t1;
	t_philosoph		*philosoph;
	unsigned int	j;

	philosoph = (t_philosoph *)ap;
	while (1)
	{
		usleep(philosoph->param.time_to_die / 4);
		gettimeofday(&t1, NULL);
		if (philosoph->param.time_to_die < ((t1.tv_sec * 1000 + \
		t1.tv_usec / 1000) - philosoph->timer) && philosoph->timer != 0)
		{
			sem_wait(philosoph->chat);
			printf("%zd %d is dead\n", \
			get_time(philosoph->param.begin_timer), philosoph->i);
			j = 0;
			while (j < philosoph->param.number_of_philosophers)
			{
				kill(philosoph->pid[j], 2);
				j++;
			}
			exit(0);
		}
	}
	return (NULL);
}
