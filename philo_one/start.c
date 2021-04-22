#include "philo_one.h"

int	global_init(t_global *global, char **argv)
{
	init_params(&global->param);
	if ((pars_params(&global->param, argv)) == -1)
		return (0);
	global->philosoph = (t_philosoph *)malloc(sizeof(t_philosoph) \
	* global->param.number_of_philosophers);
	global->prongs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* global->param.number_of_philosophers);
	global->life = (pthread_t *)malloc(sizeof(pthread_t) \
	* global->param.number_of_philosophers);
	if (!global->philosoph || !global->life || !global->prongs)
		return (fn_error("No memory allocate"));
	global->i = 0;
	return (1);
}

int	init_mutexs(t_global *global)
{
	while (global->i < global->param.number_of_philosophers)
	{
		if ((pthread_mutex_init(&global->prongs[global->i], NULL)) != 0)
			return (fn_error("No mutex\n"));
		global->i++;
	}
	if ((pthread_mutex_init(&global->chat, NULL)) != 0)
		return (fn_error("No mutex\n"));
	global->i = 0;
	return (1);
}

void	destroy_mutexs(t_global *global)
{
	global->i = 0;
	while (global->i < global->param.number_of_philosophers)
	{
		pthread_mutex_destroy(&global->prongs[global->i]);
		global->i++;
	}
	pthread_mutex_destroy(&global->chat);
}

void	init_par_philo(t_global *global)
{
	global->philosoph[global->i].life = &global->life[global->i];
	global->philosoph[global->i].timer = 0;
	global->philosoph[global->i].count_eat = \
	global->param.number_of_philosopher_must_eat;
	global->philosoph[global->i].param = global->param;
	global->philosoph[global->i].chat = &global->chat;
	global->philosoph[global->i].i = global->i + 1;
	global->philosoph[global->i].left = &global->prongs[global->i];
	global->philosoph[global->i].right = \
	&global->prongs[(global->i + 1) % \
	global->param.number_of_philosophers];
}
