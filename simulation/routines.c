#include "../philo.h"

int	eating(t_philo *philo)
{
	int	var_status;

	safe_mutex(philo->first_fork, LOCK);
	var_status = all_alive(philo, FORK);
	if (var_status != ALL_ALIVE)
	{
		safe_mutex(philo->first_fork, UNLOCK);
		return (var_status);
	}
	if (philo->settings->num_philosophers == 1)
	{
		safe_mutex(philo->first_fork, UNLOCK);
		return (ONE_DIED);
	}
	safe_mutex(philo->second_fork, LOCK);
	// has dinner just when entering
	safe_mutex(philo->meal_mtx, LOCK);
	philo->last_meal = get_time(NULL, GET, MILISECONDS);
	safe_mutex(philo->meal_mtx, UNLOCK);
	var_status = all_alive(philo, FORK2);
	if (var_status != ALL_ALIVE)
	{
		safe_mutex(philo->second_fork, UNLOCK);
		safe_mutex(philo->first_fork, UNLOCK);
		return (var_status);
	}
	precise_sleep(philo->time_to_eat, &philo->threshold);
	safe_mutex(philo->meal_mtx, LOCK);
	philo->max_meals--;
	safe_mutex(philo->meal_mtx, UNLOCK);
	if (philo->max_meals == 0)
	{
		safe_mutex(philo->status_mtx, LOCK);
		*philo->return_status = FULL;
		safe_mutex(philo->status_mtx, UNLOCK);
		safe_mutex(philo->first_fork, UNLOCK);
		safe_mutex(philo->second_fork, UNLOCK);
		return (FULL);
	}
	safe_mutex(philo->first_fork, UNLOCK);
	safe_mutex(philo->second_fork, UNLOCK);
	return (var_status);
}

long int	time_left(t_philo *philo)
{
	long int	time_left;
	long int	last_meal;

	safe_mutex(philo->meal_mtx, LOCK);
	last_meal = philo->last_meal;
	safe_mutex(philo->meal_mtx, UNLOCK);
	time_left = philo->time_to_die - (get_time(NULL, GET, MILISECONDS)
			- last_meal);
	return (time_left);
}

int	thinking(t_philo *philo)
{
	int		var_status;
	long	thinking_time;

	thinking_time = philo->time_to_die - (philo->time_to_eat
			+ philo->time_to_sleep);
	var_status = all_alive(philo, THINKING);
	if (philo->philo_id % 2 != 0 && philo->settings->num_philosophers % 2 != 0)
		precise_sleep(thinking_time / 4, &philo->threshold);
	return (var_status);
}

int	sleeping(t_philo *philo)
{
	int	var_status;

	var_status = all_alive(philo, SLEEPING);
	precise_sleep(philo->time_to_sleep, &philo->threshold);
	return (var_status);
}
