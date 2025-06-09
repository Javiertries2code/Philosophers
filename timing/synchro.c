/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:58:11 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/09 22:35:37 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	busy_wait_start(long synchro, int head_start)
{
	while (get_milisec() < synchro + SAND_CLOCK + head_start);
}
