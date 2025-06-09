/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asist_eight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:46:17 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/10 00:47:05 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_assitant_eight(t_settings *s)
{
	t_asist	*asist;

	asist = kloc(1, sizeof(t_asist));
	s->eight_asist = asist;
	asist->set = s;
	asist->time_mtx = s->time_mtx;
	assign_flags(asist);
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
	pthread_create(&asist->th_asist, NULL, &rout_four_back, (void *)asist);
}

void	*rout_four_back(void *args)
{
	t_asist	*asist;

	asist = (t_asist *)args;
	busy_wait_start(asist->synchro_t, PHILO_HEAD_START);
	asistant_monitor(asist, 4, 1);
	return (NULL);
}
