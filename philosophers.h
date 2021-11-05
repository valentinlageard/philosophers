#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_simconf {
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_eats_stop;
	long long start;
}	t_simconf;

typedef struct s_philo {
	int id;
	pthread_t thread;
	t_simconf *simconf;
	int num_meals;
	long long last_meal_time;
	int should_die;
	pthread_mutex_t *forks;
	int left_fork_taken;
	int right_fork_taken;
}	t_philo;

typedef enum {
	LEFT,
	RIGHT
} t_fork_side;

void	*philosopher_routine(void *args);

void	init_philosophers(t_philo philosophers[], pthread_mutex_t *forks, t_simconf *simconf);
pthread_mutex_t 	*init_forks(pthread_mutex_t *forks, t_simconf *simconf);

void	take_forks(t_philo *philosopher);
void	put_down_forks(t_philo *philosopher);

void	monitor(t_philo philosophers[], t_simconf *simconf);

void	ft_log(t_philo *philosopher, char *s);
int		ft_atoi(const char *nptr);
long long	timestamp(void);


#endif
