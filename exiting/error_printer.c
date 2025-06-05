/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:54:14 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/05 18:52:53 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

int	print_error(int err_id)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (err_id == INPUT_ERROR)
		ft_putstr_fd("Wrong input: Please enter:\n\t'./philo  "
			"number_of_philos  time_die  time_eat  time_sleep"
			"  [max_meals_per_philo]'.\n",
			STDERR_FILENO);
	else if (err_id == ARG_NEG)
		ft_putstr_fd("Arguments must be Positive.\n", STDERR_FILENO);
	else if (err_id == UNVALID_ARG)
		ft_putstr_fd("Enter positive numeric values\n", STDERR_FILENO);
	else if (err_id == ARG_BIG)
		ft_putstr_fd("Arguments must be smaller than"
			" MAX_INT.\n",
			STDERR_FILENO);
	else if (err_id == ARG_SMALL)
		ft_putstr_fd("Timing arguments must be greater than than 60ms.\n",
			STDERR_FILENO);
	else if (err_id == NO_PHILO)
		ft_putstr_fd("Number of philosophers must be over 0.\n", STDERR_FILENO);
	else if (err_id == NO_MEALS)
		ft_putstr_fd("Meals must be greater than 0\n", STDERR_FILENO);
	else if (err_id == MALLOC)
		ft_putstr_fd("Malloc failed.\n", STDERR_FILENO);
	return (err_id);
}

int	error_str(char *str)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
