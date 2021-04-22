#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include "philo_one_structs.h"

void	init_params(t_params *param);
int		fn_error(char *str);
int		pars_params(t_params *param, char **argv);
void	*cycle_of_life(void *param);
ssize_t	get_time(ssize_t timing);
void	fn_usleep(long tim);
int		global_init(t_global *global, char **argv);
int		init_mutexs(t_global *global);
void	destroy_mutexs(t_global *global);
void	init_par_philo(t_global *global);

#endif