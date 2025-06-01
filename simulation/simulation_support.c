/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_support.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:56:38 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/01 15:44:32 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*set_all_died(t_maitre *maitre)
{
	int	i;

	i = 0;
	while (maitre->num_philosophers > i)
	{
		safe_mutex(&maitre->status_mtx[i], LOCK);
		maitre->ret_st[i] = ONE_DIED;
		safe_mutex(&maitre->status_mtx[i], UNLOCK);
		i++;
	}
	return (NULL);
}

int	printer(t_philo *philo, char *opt)
{
	long	time;
	int		death;

	safe_mutex(philo->wrt_mtx, LOCK);
	time = get_milisec() - philo->settings->starting_time;
	safe_mutex(philo->any_death_mtx, LOCK);
	death = *philo->any_death;
	safe_mutex(philo->any_death_mtx, UNLOCK);
	if (death != ALL_ALIVE)
	{
		safe_mutex(philo->wrt_mtx, UNLOCK);
		return (ONE_DIED);
	}
	if (!strcmp(opt, FORK2))
	{
		printf("%s%ld %ld has taken a fork%s\n", get_col(opt), time,
			philo->ph_id, RST);
		printf(PINK "%ld %ld %s%s\n", time, philo->ph_id, EATING, RST);
	}
	else
	{
		printf("%s%ld %ld %s%s\n", get_col(opt), time, philo->ph_id, opt, RST);
	}
	safe_mutex(philo->wrt_mtx, UNLOCK);
	return (ALL_ALIVE);
}

char	*get_col(char *opt)
{
	int	n;

	n = ft_strlen(opt);
	if (!ft_strcmp(opt, FORK, n) || !ft_strcmp(opt, FORK2, n))
		return (BLUE);
	if (!ft_strcmp(opt, THINKING, n))
		return (YELLOW);
	if (!ft_strcmp(opt, SLEEPING, n))
		return (GREEN);
	if (!ft_strcmp(opt, DIED, n))
		return (RED);
	return (WHITE);
}

int	all_alive(t_philo *philo, char *opt)
{
	long	left_life;

	left_life = time_left(philo);
	if (left_life <= 0)
	{
		left_life = get_milisec() - philo->settings->starting_time;
		safe_mutex(philo->status_mtx, LOCK);
		*philo->return_status = ONE_DIED;
		safe_mutex(philo->status_mtx, UNLOCK);
		return (ONE_DIED);
	}
	return (printer(philo, opt));
}

int	thinking(t_philo *philo)
{
	int		status;
	long	thinking_time;

	thinking_time = philo->tt_die - (philo->time_to_eat + philo->time_to_sleep);
	status = all_alive(philo, THINKING);
	if (philo->ph_id % 2 != 0 && philo->settings->num_ph % 2 != 0)
		precise_sleep(thinking_time / 30, &philo->threshold);
	return (status);
}
