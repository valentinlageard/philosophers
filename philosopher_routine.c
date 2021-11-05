#include "philosophers.h"

/*
 * Returns 1 if killed during sleep, else 0.
 */

int ms_sleep(int ms, t_philo *philosopher) {
	long long start;
	long long t;
	long long ms_ll;

	start = timestamp();
	t = timestamp();
	ms_ll = ms;
	while (t - start < ms_ll) {
		t = timestamp();
		usleep(100);
		if (philosopher->should_die)
			return 1;
	}
	return 0;
}

int eat(t_philo * philosopher) {
	// take forks
	ft_log(philosopher, "is eating\n");
	if (ms_sleep(philosopher->simconf->time_to_eat, philosopher) != 0)
		return (1);
	philosopher->last_meal_time = timestamp();
	// put down forks
	return (0);
}

int rest(t_philo *philosopher) {
	ft_log(philosopher, "is sleeping\n");
	if (ms_sleep(philosopher->simconf->time_to_sleep, philosopher) != 0)
		return (1);
	return (0);
}

void think(t_philo *philosopher) {
	ft_log(philosopher, "is thinking\n");
}

void *philosopher_routine(void *args) {
	t_philo *philosopher;

	philosopher = (t_philo *)args;
	while (1) {
		if (eat(philosopher) != 0)
			break ;
		if (rest(philosopher) != 0)
			break ;
		think(philosopher);
		if (philosopher->should_die)
			break;
	}
	// If forks are in use, put them down
	return NULL;
}