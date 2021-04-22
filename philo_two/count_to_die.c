#include "philo_two.h"

void	*utils_count_die(t_philosoph *philosoph, int i)
{
	sem_wait(philosoph->chat);
	printf("%zd %d is dead\n", \
	get_time(philosoph[i].param.begin_timer), i + 1);
	return (NULL);
}

int	init_cycle(t_params param)
{
	usleep(param.time_to_die / 4);
	return (0);
}

void	*count_to_die(void *pr)
{
	struct timeval	t1;
	t_params		param;
	t_philosoph		*philosoph;
	unsigned int	i;

	philosoph = (t_philosoph *)pr;
	param = philosoph[0].param;
	while (1)
	{
		i = init_cycle(param);
		if (philosoph[i].counter->count_eat == param.number_of_philosophers)
			return (NULL);
		gettimeofday(&t1, NULL);
		while (i < param.number_of_philosophers)
		{
			if (param.time_to_die < ((t1.tv_sec * 1000 + \
			t1.tv_usec / 1000) - philosoph[i].timer) && philosoph[i].timer != 0)
			{
				if (philosoph[i].count_eat != 0)
					return (utils_count_die(philosoph, i));
			}
			i++;
		}
	}
	return (NULL);
}
