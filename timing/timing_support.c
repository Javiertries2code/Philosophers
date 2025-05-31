#include "../philo.h"

long int	time_left(t_philo *philo)
{
	long int	last_meal;
	long int	time_left;

	safe_mutex(philo->meal_mtx, LOCK);
	last_meal = philo->last_meal;
	safe_mutex(philo->meal_mtx, UNLOCK);
	time_left = philo->tt_die
		- (get_time(NULL, GET, MILI) - last_meal);
	return (time_left);
}

bool	too_short(t_settings *set)
{
	long	time;
	timeval	tv;

	gettimeofday(&tv, NULL);
	time = ((long)tv.tv_sec * 1e3 + tv.tv_usec / 1e3) - set->starting_time;
	if (time < set->tt_die)
		return (true);
	else
		return (false);
}
