/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:50:39 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/09 22:41:25 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

int	main(int argc, char const *argv[])
{
	int			ret;
	t_settings	*set;

	ret = SUCCESS;
	set = kloc(1, sizeof(t_settings));
	if (argc == 5 || argc == 6)
		ret = parse_input(set, argv);
	else
	{
		write(1, "Error: Incorrect number arguments\n", 35);
		free(set);
		return (EXIT_FAILURE);
	}
	if (ret)
		return (ret);
	load_settings(set, argv);
	create_mutexes(set);
	create_philos(set);
	usleep(10);
	create_assitants(set);
	join_threads(set);
	exiting(set, NULL);
	return (ret);
}
