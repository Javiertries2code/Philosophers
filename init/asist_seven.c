/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asist_seven.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:46:24 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/09 22:17:38 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_assitant_seven(t_settings *s)
{
	t_asist	*asist;

	asist = kloc(1, sizeof(t_asist));
	s->seventh_asist = asist;
	asist->set = s;
	asist->time_mtx = s->time_mtx;
	safe_mutex(asist->time_mtx, LOCK);
	asist->starting_time = s->starting_time;
	safe_mutex(asist->time_mtx, UNLOCK);
	asist->tt_die = s->tt_die;
	asist->meal_mtx = s->meal_mtx;
	asist->own_death = s->own_death;
	asist->any_death = &s->any_death;
	asist->own_death_mtx = s->own_death_mtx;
	asist->any_death_mtx = s->any_death_mtx;
	asist->status_mtx = s->st_mtx;
	asist->write_mtx = s->t_write_mtx;
	asist->feed_mtx = s->feed_mtx;
	asist->num_philosophers = s->num_ph;
	asist->philos = s->philos;
	safe_mutex(asist->status_mtx, LOCK);
	asist->ret_st = s->ret_st;
	safe_mutex(asist->status_mtx, UNLOCK);
	asist->threshold = s->threshold;
	asist->synchro_t = get_time(&s->synchro_t, CHANGE, MILI);
	pthread_create(&asist->th_asist, NULL, &rout_four_ford, (void *)asist);
}

void	*rout_four_ford(void *args)
{
	t_asist	*asist;

	asist = (t_asist *)args;
	busy_wait_start(asist->synchro_t, PHILO_HEAD_START);
	asistant_monitor(asist, 4, 0);
	return (NULL);
}
