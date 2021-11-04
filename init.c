#include "philosophers.h"

void init_philosophers(t_philo philosophers[], t_simconf simconf) {
	int i;

	i = 0;
	while (i < simconf.num_philos) {
		philosophers[i].id = i + 1;
		philosophers[i].time_to_die = simconf.time_to_die;
		philosophers[i].time_to_eat = simconf.time_to_eat;
		philosophers[i].time_to_sleep = simconf.time_to_sleep;
		i++;
	}
}