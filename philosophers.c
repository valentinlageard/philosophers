#include "philosophers.h"

//TODO: Add error management

void	start_philosopher_threads(t_philo philosophers[], int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		philosophers[i].last_meal_time = philosophers[i].simconf->start;
		pthread_create(&philosophers[i].thread,
			NULL, philosopher_routine, &philosophers[i]);
		i++;
	}
}

void	wait_philosophers(t_philo philosophers[], int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

void	simulate(t_simconf *simconf)
{
	pthread_mutex_t	forks[250];
	t_philo			philosophers[250];

	init_forks(forks, simconf);
	init_philosophers(philosophers, forks, simconf);
	simconf->start = timestamp();
	start_philosopher_threads(philosophers, simconf->num_philos);
	monitor(philosophers, simconf);
	wait_philosophers(philosophers, simconf->num_philos);
	// TODO: Destroy mutexes
}

void	parse_simconf(char **argv, t_simconf *simconf)
{
	simconf->num_philos = ft_atoi(argv[1]);
	simconf->time_to_die = ft_atoi(argv[2]);
	simconf->time_to_eat = ft_atoi(argv[3]);
	simconf->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		simconf->num_eats_stop = ft_atoi(argv[5]);
	else
		simconf->num_eats_stop = 0;
	pthread_mutex_init(&simconf->mutex_print, NULL);
}

int	main(int argc, char **argv)
{
	t_simconf	simconf;

	if (argc != 5 && argc != 6)
		return (0);
	parse_simconf(argv, &simconf);
	simulate(&simconf);
	return (0);
}
