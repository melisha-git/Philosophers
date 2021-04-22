#include "philo_one.h"

int	check_to_die(t_params param, t_philosoph *philosoph)
{
	struct timeval	t1;
	unsigned int	i;

	gettimeofday(&t1, NULL);
	i = 0;
	while (i < param.number_of_philosophers)
	{
		if (philosoph[0].count->counter_eat == param.number_of_philosophers)
			return (0);
		if (param.time_to_die < ((t1.tv_sec * 1000 \
		+ t1.tv_usec / 1000) - philosoph[i].timer) \
		&& philosoph[i].timer != 0)
		{
			if (philosoph[i].count_eat != 0)
			{
				pthread_mutex_lock(philosoph[i].chat);
				printf("%zd %d is dead\n", \
				get_time(philosoph[i].param.begin_timer), i + 1);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	*count_to_die(void *pr)
{
	t_params		param;
	t_philosoph		*philosoph;

	philosoph = (t_philosoph *)pr;
	param = philosoph[0].param;
	while (1)
	{
		usleep(param.time_to_die / 4);
		if ((check_to_die(param, philosoph)) == 0)
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_global	global;
	t_counter	count;

	if (argc != 5 && argc != 6)
		return (fn_error("Number of arguments error\n"));
	if ((global_init(&global, argv)) != 1)
		return (0);
	if ((init_mutexs(&global)) != 1)
		return (0);
	count.counter_eat = 0;
	while (global.i < global.param.number_of_philosophers)
	{
		global.philosoph[global.i].count = &count;
		init_par_philo(&global);
		pthread_create(&global.life[global.i], \
		NULL, cycle_of_life, (void *)&global.philosoph[global.i]);
		global.i++;
	}
	pthread_create(&global.count_life, \
	NULL, count_to_die, (void *)global.philosoph);
	pthread_join(global.count_life, NULL);
	destroy_mutexs(&global);
	return (0);
}
