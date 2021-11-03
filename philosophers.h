#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

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

}	t_philo;

int		ft_atoi(const char *nptr);


#endif
