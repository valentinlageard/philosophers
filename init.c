#include "philosophers.h"

void init_philosophers(t_philo philosophers[], t_simconf *simconf) {
	int i;

	i = 0;
	while (i < simconf->num_philos) {
		philosophers[i].id = i + 1;
		philosophers[i].simconf = simconf;
		philosophers[i].num_meals = 0;
		philosophers[i].last_meal_time = 0;
		philosophers[i].should_die = 0;
		i++;
	}
}