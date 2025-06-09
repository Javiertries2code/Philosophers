/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:58:11 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/10 00:48:33 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	busy_wait_start(long synchro, int head_start)
{
	while (get_milisec() < synchro + SAND_CLOCK + head_start)
		;
}
