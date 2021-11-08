/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:12:03 by valentin          #+#    #+#             */
/*   Updated: 2021/11/08 15:12:39 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	all_philosophers_should_die(t_philo philosophers[], t_simconf *simconf)
{
	int	i;

	i = 0;
	while (i < simconf->num_philos)
	{
		pthread_mutex_lock(&philosophers[i].mutex_philo);
		philosophers[i].should_die = 1;
		pthread_mutex_unlock(&philosophers[i].mutex_philo);
		i++;
	}
}

int	has_starved(t_philo *philosopher, t_simconf *simconf)
{
	pthread_mutex_lock(&philosopher->mutex_philo);
	if ((timestamp() - philosopher->last_meal_time) >= simconf->time_to_die)
	{
		ft_log(philosopher, "has died\n");
		pthread_mutex_unlock(&philosopher->mutex_philo);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->mutex_philo);
	return (0);
}

int	all_philosopher_ate_enough(t_philo *philosophers, t_simconf *simconf)
{
	int	i;
	int	finished_philosophers;

	i = 0;
	finished_philosophers = 0;
	while (i < simconf->num_philos)
	{
		if (simconf->num_eats_stop > 0)
		{
			pthread_mutex_lock(&philosophers[i].mutex_philo);
			if (philosophers[i].num_meals >= simconf->num_eats_stop)
				finished_philosophers++;
			pthread_mutex_unlock(&philosophers[i].mutex_philo);
		}
		i++;
	}
	return (finished_philosophers == simconf->num_philos
		&& simconf->num_eats_stop > 0);
}

void	monitor(t_philo philosophers[], t_simconf *simconf)
{
	int	i;
	int	starvation;

	i = 0;
	starvation = 0;
	while (1)
	{
		i = 0;
		while (i < simconf->num_philos)
		{
			if (has_starved(&philosophers[i], simconf))
			{
				starvation = 1;
				break ;
			}
			i++;
		}
		if (starvation || all_philosopher_ate_enough(philosophers, simconf))
		{
			all_philosophers_should_die(philosophers, simconf);
			break ;
		}
		usleep(1000);
	}
}
