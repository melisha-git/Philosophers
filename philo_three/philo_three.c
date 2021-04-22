#include "philo_three.h"

void	init_philo(t_global *global)
{
	global->i = 0;
	while (global->i < global->param.number_of_philosophers)
	{
		global->philosoph[global->i].pid = global->pid;
		global->philosoph[global->i].timer = 0;
		global->philosoph[global->i].i = global->i + 1;
		global->philosoph[global->i].prongs = global->prongs;
		global->philosoph[global->i].param = global->param;
		global->philosoph[global->i].chat = global->chat;
		global->philosoph[global->i].count_eat = \
		global->param.number_of_philosopher_must_eat;
		global->i++;
	}
}

void	init_global(t_global *global)
{
	global->life = (pthread_t *)malloc(sizeof(pthread_t) \
	* global->param.number_of_philosophers);
	global->pid = (pid_t *)malloc(sizeof(pid_t) \
	* global->param.number_of_philosophers);
	global->philosoph = (t_philosoph *)malloc((sizeof(t_philosoph) \
	* global->param.number_of_philosophers));
	if (!global->philosoph || !global->pid || !global->life)
		fn_error("No memory allocate\n");
	sem_unlink("prongs");
	sem_unlink("#chat");
	global->chat = sem_open("#chat", O_CREAT, 0777, 1);
	global->prongs = sem_open("prongs", O_CREAT, 0777, \
	global->param.number_of_philosophers);
	if (!(global->prongs) || !(global->chat))
		fn_error("No semaphore allocate\n");
	return (init_philo(global));
}

void	destroy_semaphore_and_pids(t_global *global)
{
	global->i = 0;
	while (global->i < global->param.number_of_philosophers)
	{
		waitpid(global->pid[global->i], &global->status, 0);
		global->i++;
	}
	sem_unlink("prongs");
	sem_unlink("#chat");
}

void	start_threads(t_global *global)
{
	pthread_create(&global->life[global->i], \
	NULL, cycle_of_life, (void *)&global->philosoph[global->i]);
	pthread_create(&global->craken, NULL, \
	count_to_die, (void *)&global->philosoph[global->i]);
	pthread_join(global->craken, NULL);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_global	global;

	if (argc != 5 && argc != 6)
		fn_error("Number of arguments error\n");
	init_params(&global.param);
	if ((pars_params(&global.param, argv)) == -1)
		return (0);
	init_global(&global);
	global.i = 0;
	while (global.i < global.param.number_of_philosophers)
	{
		global.pid[global.i] = fork();
		if (global.pid[global.i] == -1)
			return (free_pids(global.i, global.pid, global.chat));
		else if (global.pid[global.i] == 0)
			start_threads(&global);
		global.i++;
	}
	destroy_semaphore_and_pids(&global);
	return (0);
}
