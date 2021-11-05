#include "philosophers.h"

void all_philosophers_should_die(t_philo philosophers[], t_simconf *simconf) {
	int i;

	i = 0;
	while (i < simconf->num_philos) {
		philosophers[i].should_die = 1;
		i++;
	}
}

void monitor(t_philo philosophers[], t_simconf *simconf) {
	int i;
	int finished_philosophers;
	int starvation;

	i = 0;
	finished_philosophers = 0;
	starvation = 0;
	while (1) {
		i = 0;
		while (i < simconf->num_philos) {
			// Add mutex protection for death check (last_meal_time !)
			//printf("Checking philosopher %i : last_meal_time=%lli\n", philosophers[i].id, philosophers[i].last_meal_time);
			if ((timestamp() - philosophers[i].last_meal_time) >= simconf->time_to_die)
			{
				ft_log(&philosophers[i], "has died\n");
				all_philosophers_should_die(philosophers, simconf);
				starvation = 1;
				break ;
			}
			// If num_eats_stop > 0
				// If num_meals == num_eats_stop
					// finished_philosophers++
			i++;
		}
		if (starvation)
			break ;
		if (simconf->num_eats_stop > 0 && finished_philosophers == simconf->num_philos)
			break ;
		usleep(500);
	}
}