#include "philosophers.h"

void eat(t_philo * philosopher) {
	// take forks
	ft_log(philosopher, "is eating\n");
	usleep(philosopher->time_to_eat * 1000);
	// put down forks
}

void rest(t_philo *philosopher) {
	ft_log(philosopher, "is sleeping\n");
	usleep(philosopher->time_to_sleep * 1000);
}

void think(t_philo *philosopher) {
	ft_log(philosopher, "is thinking\n");
}

void * philosopher_routine(void *args) {
	t_philo *philosopher;

	philosopher = (t_philo *)args;
	while (1) {
		eat(philosopher);
		rest(philosopher);
		think(philosopher);
	}
}