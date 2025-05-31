#include "../philo.h"

void	*routine_ph(void *args)
{
	t_philo	*philo;
	int		*ret;

	philo = (t_philo *)args;
	safe_mutex(philo->status_mtx, LOCK);
	ret = philo->return_status;
	safe_mutex(philo->status_mtx, UNLOCK);
	busy_wait_start(philo->synchro_t, 0);
	safe_mutex(philo->time_mtx, LOCK);
	if (philo->settings->starting_time == 0)
		philo->settings->starting_time = get_time(NULL, GET, MILI);
	safe_mutex(philo->time_mtx, UNLOCK);
	safe_mutex(philo->time_mtx, LOCK);
	philo->last_meal = get_time(NULL, GET, MILI);
	safe_mutex(philo->time_mtx, UNLOCK);
	if (philo->ph_id % 2 == 0)
		routine_even(philo);
	else
		routine_odd(philo);
	return (ret);
}

int	routine_even(t_philo *philo)
{
	int	ret;
	int	ret2;
	int	ret3;

	while (1)
	{
		ret2 = sleeping(philo);
		if (ret2 != 0)
			return (ret2);
		ret3 = thinking(philo);
		if (ret3 != 0)
			return (ret3);
		ret = eating(philo);
		if (ret != 0)
			return (ret);
	}
}

int	routine_odd(t_philo *philo)
{
	int	ret;
	int	ret2;
	int	ret3;

	while (1)
	{
		ret3 = thinking(philo);
		if (ret3 != 0)
			return (ret3);
		ret = eating(philo);
		if (ret != 0)
			return (ret);
		ret2 = sleeping(philo);
		if (ret2 != 0)
			return (ret2);
	}
}
