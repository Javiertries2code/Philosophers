/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:55:46 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/01 15:56:28 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_error(int error_return)
{
	if (!error_return)
		return ;
	if (error_return == ENOMEM)
		exit_on_error("low memory to initialize the mutex.");
	if (error_return == EAGAIN)
		exit_on_error("Lacked the necessary resources (other than memory).");
	if (error_return == EPERM)
		exit_on_error("Needs privilege to perform the operation.");
}

void	lock_error(int error_return)
{
	if (!error_return)
		return ;
	if (error_return == EDEADLK)
		exit_on_error("Current thread already owns the mutex.");
	if (error_return == EAGAIN)
		exit_on_error("Max number of recursive locks for mutex was exceeded.");
	if (error_return == EOWNERDEAD)
		exit_on_error("The last owner terminated while holding the mutex.");
	if (error_return == ENOTRECOVERABLE)
		exit_on_error("Mutex left irrecoverable by the mutexs previous owner.");
	if (error_return == ENOMEM)
		exit_on_error("Limit of simultaneously held mutexes exceeded.");
}

void	destroy_error(int error_return)
{
	if (!error_return)
		return ;
	if (error_return == EBUSY)
		exit_on_error("Attempt to destroy object while locked.");
	if (error_return == EINVAL)
		exit_on_error("The value specified by mutex not valid.");
}

void	unlock_error(int error_return)
{
	if (!error_return)
		return ;
	if (error_return == EPERM)
		exit_on_error("The current thread does not own the mutex.");
}

void	safe_mutex(pthread_mutex_t *mtx, t_mtx_option option)
{
	if (option == INIT)
		init_error(pthread_mutex_init(mtx, NULL));
	if (option == LOCK)
		lock_error(pthread_mutex_lock(mtx));
	if (option == UNLOCK)
		unlock_error(pthread_mutex_unlock(mtx));
	if (option == DESTROY)
		destroy_error(pthread_mutex_destroy(mtx));
}
