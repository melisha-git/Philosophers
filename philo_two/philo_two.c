#include "philo_two.h"

int	init_sem(t_global *global)
{
	sem_unlink("#chat");
	sem_unlink("prongs");
	global->counter.count_prongs = global->param.number_of_philosophers;
	global->counter.count_philosopher = global->param.number_of_philosophers;
	global->counter.count_eat = 0;
	global->prongs = sem_open("prongs", O_CREAT, 0777, \
	global->param.number_of_philosophers);
	global->chat = sem_open("#chat", O_CREAT, 0777, 1);
	if ((global->prongs == SEM_FAILED) || (global->chat == SEM_FAILED))
	{
		printf("No semaphore allocate\n");
		return (0);
	}
	global->philosoph = (t_philosoph *)malloc(sizeof(t_philosoph) \
	* global->param.number_of_philosophers);
	global->life = (pthread_t *)malloc(sizeof(pthread_t) \
	* global->param.number_of_philosophers);
	global->mon = (char *)malloc(sizeof(char) \
	* global->param.number_of_philosophers + 1);
	if (!global->philosoph || !global->life || !global->mon)
		return (fn_error("No memory allocate"));
	global->mon[global->param.number_of_philosophers] = '\0';
	memset(global->mon, '0', global->param.number_of_philosophers);
	return (1);
}

void	init_param_philo(t_global *global)
{
	global->philosoph[global->i].wait = global->mon;
	global->philosoph[global->i].counter = &global->counter;
	global->philosoph[global->i].prongs = global->prongs;
	global->philosoph[global->i].chat = global->chat;
	global->philosoph[global->i].life = &global->life[global->i];
	global->philosoph[global->i].param = global->param;
	global->philosoph[global->i].i = global->i + 1;
	global->philosoph[global->i].count_eat = \
	global->param.number_of_philosopher_must_eat;
	global->philosoph[global->i].timer = 0;
}

int	main(int argc, char **argv)
{
	t_global	global;

	if (argc != 5 && argc != 6)
		return (fn_error("Number of arguments error\n"));
	init_params(&global.param);
	if ((pars_params(&global.param, argv)) == -1)
		return (0);
	if ((init_sem(&global)) != 1)
		return (0);
	global.i = 0;
	while (global.i < global.param.number_of_philosophers)
	{
		init_param_philo(&global);
		pthread_create(&global.life[global.i], \
		NULL, cycle_of_life, (void *)&global.philosoph[global.i]);
		global.i++;
	}
	pthread_create(&global.waiter, NULL, \
	cycle_waiter, (void *)global.philosoph);
	pthread_create(&global.count_life, NULL, \
	count_to_die, (void *)global.philosoph);
	pthread_join(global.count_life, NULL);
	sem_unlink("#chat");
	sem_unlink("prongs");
	return (0);
}
