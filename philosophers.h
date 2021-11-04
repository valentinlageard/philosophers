#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_simconf {
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_eats_stop;
}	t_simconf;

typedef struct s_fork {
	pthread_mutex_t mutex;
}	t_fork;

typedef struct s_philo {
	int id;
	pthread_t thread;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_eats_stop;
}	t_philo;

void	*philosopher_routine(void *args);

void	init_philosophers(t_philo philosophers[], t_simconf simconf);

void	ft_log(t_philo *philosopher, char *s);
int		ft_atoi(const char *nptr);


#endif
