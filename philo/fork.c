/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:11:49 by valentin          #+#    #+#             */
/*   Updated: 2021/11/08 15:11:51 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	manage_single_philo(t_philo *philosopher,
	int left_fork_idx, int right_fork_idx)
{
	if (left_fork_idx == right_fork_idx)
	{
		ms_sleep(philosopher->simconf->time_to_die + 1, philosopher);
		return (1);
	}
	return (0);
}

int	take_fork(t_philo *philosopher, int fork_idx, t_fork_side fork_side)
{
	pthread_mutex_t	*fork;

	fork = &philosopher->forks[fork_idx];
	pthread_mutex_lock(fork);
	if (fork_side == LEFT)
		philosopher->left_fork_taken = 1;
	else
		philosopher->right_fork_taken = 1;
	pthread_mutex_lock(&philosopher->mutex_philo);
	if (philosopher->should_die)
	{
		pthread_mutex_unlock(&philosopher->mutex_philo);
		return (1);
	}
	ft_log(philosopher, "has taken a fork\n");
	pthread_mutex_unlock(&philosopher->mutex_philo);
	return (0);
}

int	take_forks(t_philo *philosopher)
{
	int	left_fork_idx;
	int	right_fork_idx;
	int	ret;

	left_fork_idx = philosopher->id - 1;
	right_fork_idx = philosopher->id - 2;
	if (right_fork_idx < 0)
		right_fork_idx = philosopher->simconf->num_philos - 1;
	if (philosopher->id % 2 == 0)
	{
		if (take_fork(philosopher, right_fork_idx, RIGHT) != 0)
			return (1);
		ret = take_fork(philosopher, left_fork_idx, LEFT);
	}
	else
	{
		if (take_fork(philosopher, left_fork_idx, LEFT) != 0)
			return (1);
		if (manage_single_philo(philosopher, left_fork_idx, right_fork_idx))
			return (1);
		ret = take_fork(philosopher, right_fork_idx, RIGHT);
	}
	return (ret);
}

void	put_down_fork(t_philo *philosopher, int fork_idx, t_fork_side fork_side)
{
	pthread_mutex_t	*fork;

	fork = &philosopher->forks[fork_idx];
	pthread_mutex_unlock(fork);
	if (fork_side == LEFT)
		philosopher->left_fork_taken = 0;
	else
		philosopher->right_fork_taken = 0;
}

void	put_down_forks(t_philo *philosopher)
{
	int	left_fork_idx;
	int	right_fork_idx;

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
		if (philosopher->left_fork_taken)
			put_down_fork(philosopher, left_fork_idx, LEFT);
		if (philosopher->right_fork_taken)
			put_down_fork(philosopher, right_fork_idx, RIGHT);
	}
}
