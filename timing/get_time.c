/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:58:09 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/01 13:58:10 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(timeval *tv, timing_options operation, timing_options units)
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

long	to_microsec(timeval *tv)
{
	return ((long)tv->tv_sec * 1e6 + tv->tv_usec);
}

long	to_milisec(timeval *tv)
{
	return ((long)tv->tv_sec * 1e3 + tv->tv_usec / 1e3);
}

long	get_microsec(void)
{
	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1e6 + tv.tv_usec);
}

long	get_milisec(void)
{
	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}
