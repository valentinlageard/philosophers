#include "philosophers.h"

void take_fork(t_philo *philosopher, int fork_idx, t_fork_side fork_side)
{
	pthread_mutex_t *fork;

	fork = &philosopher->forks[fork_idx];
	pthread_mutex_lock(fork);
	if (fork_side == LEFT)
		philosopher->left_fork_taken = 1;
	else
		philosopher->right_fork_taken = 1;
	ft_log(philosopher, "has taken a fork\n");
}

void take_forks(t_philo *philosopher)
{
	int left_fork_idx;
	int right_fork_idx;

	left_fork_idx = philosopher->id - 1;
	right_fork_idx = philosopher->id - 2;
	if (right_fork_idx < 0)
		right_fork_idx = philosopher->simconf->num_philos - 1;
	if (philosopher->id % 2 == 0)
	{
		take_fork(philosopher, right_fork_idx, RIGHT);
		take_fork(philosopher, left_fork_idx, LEFT);
	}
	else
	{
		take_fork(philosopher, left_fork_idx, LEFT);
		take_fork(philosopher, right_fork_idx, RIGHT);
	}
}

void put_down_fork(t_philo *philosopher, int fork_idx, t_fork_side fork_side)
{
	pthread_mutex_t *fork;

	fork = &philosopher->forks[fork_idx];
	pthread_mutex_unlock(fork);
	if (fork_side == LEFT)
		philosopher->left_fork_taken = 0;
	else
		philosopher->right_fork_taken = 0;
	ft_log(philosopher, "has put down a fork\n");
}

void put_down_forks(t_philo *philosopher)
{
	int left_fork_idx;
	int right_fork_idx;

	left_fork_idx = philosopher->id - 1;
	right_fork_idx = philosopher->id - 2;
	if (right_fork_idx < 0)
		right_fork_idx = philosopher->simconf->num_philos - 1;

	if (philosopher->id % 2 == 0)
	{
		if (philosopher->right_fork_taken)
			put_down_fork(philosopher, right_fork_idx, RIGHT);
		if (philosopher->left_fork_taken)
			put_down_fork(philosopher, left_fork_idx, LEFT);
	}
	else
	{
		if (philosopher->left_fork_taken) {
			put_down_fork(philosopher, left_fork_idx, LEFT);
		}
		if (philosopher->right_fork_taken)
			put_down_fork(philosopher, right_fork_idx, RIGHT);
	}

}