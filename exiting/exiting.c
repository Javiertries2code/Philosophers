/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:54:20 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/05 23:53:17 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	free_allocated(t_settings *s)
{
	free(s->t_write_mtx);
	free(s->time_mtx);
	free(s->st_mtx);
	free(s->meal_mtx);
	free(s->philo_status);
	free(s->ret_st);
	free(s->philos);
	free(s->mutexes);
	free(s->asist);
	free(s->nd_asist);
	free(s->feed_mtx);
	free(s->any_death_mtx);
	free(s->own_death_mtx);
	free(s->own_death);
	free(s);
}

static void	destroy_mutexes(t_settings *s)
{
	int	i;

	i = 0;
	if (s->t_write_mtx)
		pthread_mutex_destroy(s->t_write_mtx);
	if (s->time_mtx)
		pthread_mutex_destroy(s->time_mtx);
	if (s->any_death_mtx)
		pthread_mutex_destroy(s->any_death_mtx);
	while (i < s->num_ph)
	{
		pthread_mutex_destroy(&s->mutexes[i]);
		pthread_mutex_destroy(&s->st_mtx[i]);
		pthread_mutex_destroy(&s->meal_mtx[i]);
		pthread_mutex_destroy(&s->own_death_mtx[i]);
		i++;
	}
}

void	free_memory(t_settings *s)
{
	if (!s)
		return ;
	destroy_mutexes(s);
	free_allocated(s);
}

void	exit_on_error(char *str)
{
	write(2, "ERROR\n", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	exiting(t_settings *settings, char *str)
{
	if (str != NULL)
		exit_on_error(str);
	free_memory(settings);
	exit(SUCCESS);
}
