#include "philo_two.h"

unsigned int	fill_params(char *str)
{
	short			i;
	unsigned int	result;

	i = -1;
	result = 0;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Numeric argument required\n");
			return (0);
		}
		result = result * 10 + (str[i] - '0');
	}
	return (result);
}

int	validation_params(t_params *param)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	param->begin_timer = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	if (param->number_of_philosophers < 2)
		return (fn_error("At least two philosophers"));
	if (param->time_to_die < 1)
		return (fn_error("Can't be zero or minus"));
	if (param->time_to_eat < 1)
		return (fn_error("Can't be zero or minus"));
	if (param->time_to_sleep < 1)
		return (fn_error("Can't be zero or minus"));
	if (param->number_of_philosopher_must_eat < 1 \
	&& (int)param->number_of_philosopher_must_eat != -1)
		return (fn_error("Can't be zero or minus"));
	return (0);
}

int	pars_params(t_params *param, char **argv)
{
	short	i;

	i = 1;
	while (argv[i])
	{
		if (i == 1)
			param->number_of_philosophers = fill_params(argv[i]);
		if (i == 2)
			param->time_to_die = fill_params(argv[i]);
		if (i == 3)
			param->time_to_eat = fill_params(argv[i]);
		if (i == 4)
			param->time_to_sleep = fill_params(argv[i]);
		if (i == 5)
			param->number_of_philosopher_must_eat = fill_params(argv[i]);
		i++;
	}
	return (validation_params(param));
}

void	init_params(t_params *param)
{
	param->number_of_philosophers = -1;
	param->time_to_die = -1;
	param->time_to_eat = -1;
	param->time_to_sleep = -1;
	param->number_of_philosopher_must_eat = -1;
}
