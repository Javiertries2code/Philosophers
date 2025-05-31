#include "../philo.h"

int	lock_first_fork_and_check(t_philo *philo)
{
	int	status;

	safe_mutex(philo->first_fork, LOCK);
	status = all_alive(philo, FORK);
	if (status != ALL_ALIVE)
		safe_mutex(philo->first_fork, UNLOCK);
	return (status);
}

void	handle_last_meal_update(t_philo *philo)
{
	safe_mutex(philo->meal_mtx, LOCK);
	philo->last_meal = get_time(NULL, GET, MILI);
	safe_mutex(philo->meal_mtx, UNLOCK);
}

int	handle_meal_count_and_status(t_philo *philo)
{
	safe_mutex(philo->meal_mtx, LOCK);
	philo->max_meals--;
	safe_mutex(philo->meal_mtx, UNLOCK);
	if (philo->max_meals == 0)
	{
		safe_mutex(philo->status_mtx, LOCK);
		*philo->return_status = FULL;
		safe_mutex(philo->status_mtx, UNLOCK);
		return (FULL);
	}
	return (ALL_ALIVE);
}

int	eating(t_philo *philo)
{
	int	status;

	status = lock_first_fork_and_check(philo);
	if (status != ALL_ALIVE)
		return (status);
	if (philo->settings->num_ph == 1)
	{
		safe_mutex(philo->first_fork, UNLOCK);
		return (ONE_DIED);
	}
	safe_mutex(philo->second_fork, LOCK);
	handle_last_meal_update(philo);
	status = all_alive(philo, FORK2);
	if (status != ALL_ALIVE)
	{
		safe_mutex(philo->first_fork, UNLOCK);
		safe_mutex(philo->second_fork, UNLOCK);
		return (status);
	}
	precise_sleep(philo->time_to_eat, &philo->threshold);
	status = handle_meal_count_and_status(philo);
	safe_mutex(philo->first_fork, UNLOCK);
	safe_mutex(philo->second_fork, UNLOCK);
	return (status);
}

int	sleeping(t_philo *philo)
{
	int	status;

	status = all_alive(philo, SLEEPING);
	precise_sleep(philo->time_to_sleep, &philo->threshold);
	return (status);
}
