#include "philosophers.h"

void eat(t_philo * philosopher, t_fork ** forks) {
	// take forks
	log(philosopher, "is eating\n");
	usleep(philosopher->time_to_eat * 1000);
	// put down forks
}

void sleep(t_philo *philosopher) {
	log(philosopher, "is sleeping\n");
	usleep(philosopher->time_to_sleep * 1000);
}

void think(t_philo *philosopher) {
	log(philosopher, "is thinking\n");
	usleep(philosopher->time_to_think * 1000);
}

void philosopher_routine(t_philo *philosopher, t_fork ** forks) {
	while 1 {
		eat(philosopher, forks);
		sleep(philosopher);
		sleep(philosopher);
	}
}