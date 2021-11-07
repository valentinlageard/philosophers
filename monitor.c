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
	starvation = 0;
	while (1) {
		finished_philosophers = 0;
		i = 0;
		while (i < simconf->num_philos) {
			pthread_mutex_lock(&philosophers[i].mutex_philo);
			if ((timestamp() - philosophers[i].last_meal_time) >= simconf->time_to_die)
			{
				ft_log(&philosophers[i], "has died\n");
				all_philosophers_should_die(philosophers, simconf);
				starvation = 1;
				pthread_mutex_unlock(&philosophers[i].mutex_philo);
				break ;
			}
			if (simconf->num_eats_stop > 0) {
				if (philosophers[i].num_meals >= simconf->num_eats_stop)
					finished_philosophers++;
			}
			pthread_mutex_unlock(&philosophers[i].mutex_philo);
			i++;
		}
		if (starvation)
			break ;
		if (simconf->num_eats_stop > 0 && finished_philosophers == simconf->num_philos)
		{
			all_philosophers_should_die(philosophers, simconf);
			break ;
		}
		usleep(1000);
	}
}