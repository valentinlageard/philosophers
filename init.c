/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:11:57 by valentin          #+#    #+#             */
/*   Updated: 2021/11/08 15:12:37 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosophers(t_philo philosophers[],
			pthread_mutex_t *forks, t_simconf *simconf) {
	int	i;

	i = 0;
	while (i < simconf->num_philos)
	{
		philosophers[i].id = i + 1;
		philosophers[i].simconf = simconf;
		philosophers[i].num_meals = 0;
		philosophers[i].last_meal_time = 0;
		philosophers[i].should_die = 0;
		pthread_mutex_init(&philosophers[i].mutex_philo, NULL);
		philosophers[i].forks = forks;
		philosophers[i].left_fork_taken = 0;
		philosophers[i].right_fork_taken = 0;
		i++;
	}
}

pthread_mutex_t	*init_forks(pthread_mutex_t *forks, t_simconf *simconf)
{
	int	i;

	i = 0;
	while (i < simconf->num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
