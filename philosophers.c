#include "philosophers.h"

void start_philosopher_threads(t_philo philosophers[], int n) {
	int i;

	i = 0;
	while (i < n) {
		pthread_create(&philosophers[i].thread, NULL, philosopher_routine, (t_philo *)&philosophers[i]);
		i++;
	}
}

void wait_philosophers(t_philo philosophers[], int n) {
	int i;

	i = 0;
	while (i < n) {
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

void simulate(t_simconf simconf) {
	// Init forks
	t_philo philosophers[simconf.num_philos];
	init_philosophers(philosophers, simconf);
	start_philosopher_threads(philosophers, simconf.num_philos);
	wait_philosophers(philosophers, simconf.num_philos);
	// Start death
}

void parse_simconf(char ** argv, t_simconf * simconf) {
	simconf->num_philos = ft_atoi(argv[1]);
	simconf->time_to_die = ft_atoi(argv[2]);
	simconf->time_to_eat = ft_atoi(argv[3]);
	simconf->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		simconf->num_eats_stop = ft_atoi(argv[5]);
}

int main(int argc, char ** argv) {
	t_simconf simconf;

	if (argc != 5 && argc != 6)
		return (0);
	parse_simconf(argv, &simconf);
	simulate(simconf);
	return 0;
}