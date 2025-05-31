#include "../philo.h"

static int	lock_first_fork_and_check(t_philo *philo)
{
	int	status;

	safe_mutex(philo->first_fork, LOCK);
	status = all_alive(philo, FORK);
	if (status != ALL_ALIVE)
		safe_mutex(philo->first_fork, UNLOCK);
	return (status);
}

static void	handle_last_meal_update(t_philo *philo)
{
	safe_mutex(philo->meal_mtx, LOCK);
	philo->last_meal = get_time(NULL, GET, MILI);
	safe_mutex(philo->meal_mtx, UNLOCK);
}

static int	handle_meal_count_and_status(t_philo *philo)
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
	int	var_status;

	var_status = lock_first_fork_and_check(philo);
	if (var_status != ALL_ALIVE)
		return (var_status);
	if (philo->settings->num_ph == 1)
	{
		safe_mutex(philo->first_fork, UNLOCK);
		return (ONE_DIED);
	}
	safe_mutex(philo->second_fork, LOCK);
	handle_last_meal_update(philo);
	var_status = all_alive(philo, FORK2);
	if (var_status != ALL_ALIVE)
	{
		safe_mutex(philo->first_fork, UNLOCK);
		safe_mutex(philo->second_fork, UNLOCK);
		return (var_status);
	}
	precise_sleep(philo->time_to_eat, &philo->threshold);
	var_status = handle_meal_count_and_status(philo);
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
	time_left = philo->tt_die
		- (get_time(NULL, GET, MILI) - last_meal);
	return (time_left);
}

int	thinking(t_philo *philo)
{
	int	var_status;
	long	thinking_time;

	thinking_time = philo->tt_die
		- (philo->time_to_eat + philo->time_to_sleep);
	var_status = all_alive(philo, THINKING);
	if (philo->ph_id % 2 != 0 && philo->settings->num_ph % 2 != 0)
		precise_sleep(thinking_time / 30, &philo->threshold);
	return (var_status);
}

int	sleeping(t_philo *philo)
{
	int	var_status;

	var_status = all_alive(philo, SLEEPING);
	precise_sleep(philo->time_to_sleep, &philo->threshold);
	return (var_status);
}
