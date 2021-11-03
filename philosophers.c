#include "philosophers.h"

void simulate(t_simconf simconf) {
	// Init forks
	// Init philosophers
	// Start philosopher threads
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
	parse_simconf(&simconf);
	simulate(simconf);
	return 0;
}