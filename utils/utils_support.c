/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:58:21 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/01 15:52:52 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	support_read_returns(t_settings *settings)
{
	int	i;

	i = -1;
	while (settings->num_ph > ++i)
	{
		write(1, "read returns\n", 13);
		printf("philo [%ld]return_status = %d\n",
			settings->philos[i].ph_id, (int)(settings->ret_st[i]));
	}
}

void	print_data(t_settings *settings, char *str)
{
	long int	i;

	printf("\n%s\n", str);
	i = 0;
	while (i < settings->num_ph)
	{
		if (&settings->mutexes[i] != NULL)
			write(1, "the mutex was set\n", 19);
		else
			write(1, "the mutex is null", 18);
		i++;
	}
}

void	write_function(t_settings *settings, char *str)
{
	safe_mutex(settings->t_write_mtx, LOCK);
	write(1, str, ft_strlen(str));
	safe_mutex(settings->t_write_mtx, UNLOCK);
}
