#include "philosophers.h"

long long timestamp(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_log(t_philo * philosopher, char *s) {
	long long now;

	now = timestamp() - philosopher->simconf->start;
	printf("%lli philosopher %d %s",now, philosopher->id, s);
}

static int	ft_is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *nptr)
{
	int i;
	int sign_counter;
	int result;

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