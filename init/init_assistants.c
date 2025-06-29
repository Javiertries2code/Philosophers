/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assistants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:56:18 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/10 00:42:44 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	assign_flags(t_asist *asist)
{
	safe_mutex(asist->time_mtx, LOCK);
	asist->starting_time = asist->set->starting_time;
	safe_mutex(asist->time_mtx, UNLOCK);
}

void	create_assitants(t_settings *set)
{
	create_assitant_one(set);
	if (set->num_ph > 20 && set->num_ph <= 39)
		create_assitant_two(set);
	if (set->num_ph > 30 && set->num_ph <= 60)
	{
		create_assitant_three(set);
		create_assitant_four(set);
	}
	if (set->num_ph > 60 && set->num_ph <= 100)
	{
		create_assitant_five(set);
		create_assitant_six(set);
	}
	if (set->num_ph > 100)
	{
		create_assitant_seven(set);
		create_assitant_eight(set);
	}
}

int	check_philo_state(t_asist *asist, int i)
{
	int		status;

	if (time_left(&asist->philos[i]) > 0)
		return (1);
	safe_mutex(&asist->status_mtx[i], LOCK);
	status = asist->ret_st[i];
	safe_mutex(&asist->status_mtx[i], UNLOCK);
	if (status != FULL)
		return (handle_philo_death(asist, i));
	safe_mutex(asist->feed_mtx, LOCK);
	status = asist->set->all_full;
	safe_mutex(asist->feed_mtx, UNLOCK);
	return (status != 0);
}

int	handle_philo_death(t_asist *asist, int i)
{
	long	time;

	safe_mutex(asist->write_mtx, LOCK);
	time = get_milisec() - asist->set->starting_time;
	safe_mutex(asist->any_death_mtx, LOCK);
	if (*asist->any_death == ALL_ALIVE)
	{
		printf("%ld %d died\n", time, i + 1);
		*asist->any_death = ONE_DIED;
	}
	safe_mutex(asist->any_death_mtx, UNLOCK);
	usleep(asist->num_philosophers * 100);
	safe_mutex(asist->write_mtx, UNLOCK);
	return (0);
}

void	asistant_monitor(t_asist *asist, int step, int reverse)
{
	int	i;

	while (1)
	{
		if (reverse)
			i = asist->num_philosophers - 1;
		else
			i = 0;
		while ((reverse && i >= 0) || (!reverse && i < asist->num_philosophers))
		{
			if (!too_short(asist->starting_time, asist->tt_die))
			{
				if (!check_philo_state(asist, i))
					return ;
			}
			if (reverse)
				i -= step;
			else
				i += step;
		}
		usleep(1);
	}
}
