/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:55:46 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/01 13:55:48 by jbravo           ###   ########.fr       */
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
		exit_on_error("Lacked the necessary resources (other than memory) to initialize mutex.");
	if (error_return == EPERM)
		exit_on_error("The caller does not have privilege to perform the operation.");
}

void	lock_error(int error_return)
{
	if (!error_return)
		return ;
	if (error_return == EDEADLK)
		exit_on_error("Current thread already owns the mutex.");
	if (error_return == EAGAIN)
		exit_on_error("The mutex wasnt acquired because max number of recursive locks for mutex was exceeded.");
	if (error_return == EOWNERDEAD)
		exit_on_error("The last owner of this mutex terminated while holding the mutex.");
	if (error_return == ENOTRECOVERABLE)
		exit_on_error("The mutex you are trying to acquire was protecting state left irrecoverable by the mutexs previous owner.");
	if (error_return == ENOMEM)
		exit_on_error("Limit on the number of simultaneously held mutexes has been exceeded.");
}

void	destroy_error(int error_return)
{
	if (!error_return)
		return ;
	if (error_return == EBUSY)
		exit_on_error("Attempt to destroy object referenced by mutex while it was locked.");
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
