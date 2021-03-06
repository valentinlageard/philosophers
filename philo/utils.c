/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:12:20 by valentin          #+#    #+#             */
/*   Updated: 2021/11/08 16:10:44 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_all_mutexes(pthread_mutex_t *forks,
	t_philo *philosophers, t_simconf *simconf)
{
	int	i;

	i = 0;
	while (i < simconf->num_philos)
	{
		pthread_mutex_destroy(&philosophers[i].mutex_philo);
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&simconf->mutex_print);
}

long long	timestamp(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_log(t_philo *philosopher, char *s)
{
	long long	now;

	now = timestamp() - philosopher->simconf->start;
	pthread_mutex_lock(&philosopher->simconf->mutex_print);
	printf("%lli %d %s", now, philosopher->id, s);
	pthread_mutex_unlock(&philosopher->simconf->mutex_print);
}

static int	ft_is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign_counter;
	int	result;

	i = 0;
	sign_counter = 0;
	result = 0;
	while (ft_is_space(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign_counter++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10;
		result = result + nptr[i] - '0';
		i++;
	}
	if (sign_counter)
		result = -result;
	return (result);
}
