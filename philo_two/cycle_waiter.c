#include "philo_two.h"

void	*cycle_waiter(void *ap)
{
	unsigned int	i;
	unsigned int	number_philo;
	char			*wait;
	t_philosoph		*philosoph;

	i = 0;
	philosoph = (t_philosoph *)ap;
	wait = philosoph[0].wait;
	number_philo = philosoph[0].param.number_of_philosophers;
	while (1)
	{
		i = 0;
		while (i < number_philo)
		{
			if (wait[i] == '1' && philosoph[i].counter->count_prongs >= 2)
			{
				sem_wait(philosoph[i].prongs);
				sem_wait(philosoph[i].prongs);
				philosoph->counter->count_prongs -= 2;
				wait[i] = '0';
			}
			i++;
		}
	}
	return (NULL);
}
