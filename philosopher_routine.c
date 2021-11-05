#include "philosophers.h"

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
	take_forks(philosopher);
	ft_log(philosopher, "is eating\n");
	pthread_mutex_lock(&philosopher->mutex_philo);
	philosopher->last_meal_time = timestamp();
	pthread_mutex_unlock(&philosopher->mutex_philo);
	if (ms_sleep(philosopher->simconf->time_to_eat, philosopher) != 0) {
		return (1);
	}
	put_down_forks(philosopher);
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
	if (philosopher->id % 2 == 1)
		usleep(1000);
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
	put_down_forks(philosopher);
	return NULL;
}