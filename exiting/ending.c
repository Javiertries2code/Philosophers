/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:51:20 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/10 00:54:54 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	set_em_full(t_settings *settings)
{
	int		i;
	void	*ret;

	i = -1;
	while (settings->num_ph > ++i)
	{
		pthread_join(settings->philos[i].thread_id, &ret);
		if (*(int *)ret == FULL)
		{
			safe_mutex(settings->feed_mtx, LOCK);
			settings->all_full--;
			safe_mutex(settings->feed_mtx, UNLOCK);
		}
	}
}

void	join_threads(t_settings *settings)
{
	set_em_full(settings);
	pthread_join(settings->asist->th_asist, NULL);
	if (settings->nd_asist)
		pthread_join(settings->nd_asist->th_asist, NULL);
	if (settings->third_asist)
		pthread_join(settings->third_asist->th_asist, NULL);
	if (settings->fourth_asist)
		pthread_join(settings->fourth_asist->th_asist, NULL);
	if (settings->fifth_asist)
		pthread_join(settings->fifth_asist->th_asist, NULL);
	if (settings->sixth_asist)
		pthread_join(settings->sixth_asist->th_asist, NULL);
	if (settings->seventh_asist)
		pthread_join(settings->seventh_asist->th_asist, NULL);
	if (settings->eight_asist)
		pthread_join(settings->eight_asist->th_asist, NULL);
}
