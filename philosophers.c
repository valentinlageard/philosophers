/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:12:11 by valentin          #+#    #+#             */
/*   Updated: 2021/11/08 16:11:36 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_philosopher_threads(t_philo philosophers[], int n)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < n)
	{
		philosophers[i].last_meal_time = philosophers[i].simconf->start;
		if (pthread_create(&philosophers[i].thread,
				NULL, philosopher_routine, &philosophers[i]) != 0)
		{
			error = 1;
			i--;
			break ;
		}
		i++;
	}
	while (error && i >= 0)
	{
		pthread_detach(philosophers[i].thread);
		i--;
	}
	if (error)
		all_philosophers_should_die(philosophers, philosophers[0].simconf);
	return (error);
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

int	simulate(t_simconf *simconf)
{
	pthread_mutex_t	forks[1000];
	t_philo			philosophers[1000];

	init_forks(forks, simconf);
	init_philosophers(philosophers, forks, simconf);
	simconf->start = timestamp();
	if (start_philosopher_threads(philosophers, simconf->num_philos) != 0)
	{
		destroy_all_mutexes(forks, philosophers, simconf);
		return (1);
	}
	monitor(philosophers, simconf);
	wait_philosophers(philosophers, simconf->num_philos);
	destroy_all_mutexes(forks, philosophers, simconf);
	return (0);
}

int	parse_simconf(char **argv, t_simconf *simconf)
{
	simconf->num_philos = ft_atoi(argv[1]);
	if (simconf->num_philos > 1000 || simconf->num_philos < 1)
		return (1);
	simconf->time_to_die = ft_atoi(argv[2]);
	simconf->time_to_eat = ft_atoi(argv[3]);
	simconf->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		simconf->num_eats_stop = ft_atoi(argv[5]);
	else
		simconf->num_eats_stop = 0;
	pthread_mutex_init(&simconf->mutex_print, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_simconf	simconf;

	if (argc != 5 && argc != 6)
		return (1);
	if (parse_simconf(argv, &simconf) != 0)
	{
		printf("Error: philosopher number is invalid\n");
		return (1);
	}
	if (simulate(&simconf) != 0)
	{
		printf("Error: pthread_create couldn't create a thread\n");
		return (1);
	}
	return (0);
}
