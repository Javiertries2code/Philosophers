/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:58:14 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/06 00:30:12 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long int	time_left(t_philo *philo)
{
	long int	last_meal;
	long int	time_left;

	safe_mutex(philo->meal_mtx, LOCK);
	last_meal = philo->last_meal;
	safe_mutex(philo->meal_mtx, UNLOCK);
	time_left = philo->tt_die - (get_time(NULL, GET, MILI) - last_meal);
	return (time_left);
}

bool	too_short(long starting_time, long tt_die)
{
	long			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = ((long)tv.tv_sec * 1e3 + tv.tv_usec / 1e3) - starting_time;
	if (time < tt_die)
		{
			printf("too_soort Time left: %ld\n", time);
			return (true);
		}
	else
		return (false);
}

/*
bool	too_short(t_settings *set)
{
	long			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	safe_mutex(set->time_mtx, LOCK);
	time = ((long)tv.tv_sec * 1e3 + tv.tv_usec / 1e3) - set->starting_time;
	safe_mutex(set->time_mtx, UNLOCK);
	if (time < set->tt_die)
		return (true);
	else
		return (false);
}*/
