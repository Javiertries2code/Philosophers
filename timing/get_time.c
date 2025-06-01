/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:58:09 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/01 16:42:27 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(struct timeval *tv, t_timing_opt operation, t_timing_opt units)
{
	if (operation == GET)
	{
		if (units == MILI)
			return (get_milisec());
		if (units == MICRO)
			return (get_microsec());
	}
	if (operation == CHANGE)
	{
		if (units == MILI)
			return ((long)tv->tv_sec * 1e3 + tv->tv_usec / 1e3);
		if (units == MICRO)
			return ((long)tv->tv_sec * 1e6 + tv->tv_usec);
	}
	return (2);
}

long	to_microsec(struct timeval *tv)
{
	return ((long)tv->tv_sec * 1e6 + tv->tv_usec);
}

long	to_milisec(struct timeval *tv)
{
	return ((long)tv->tv_sec * 1e3 + tv->tv_usec / 1e3);
}

long	get_microsec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1e6 + tv.tv_usec);
}

long	get_milisec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}
