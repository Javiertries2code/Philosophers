/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:56:32 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/01 18:11:54 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str)
{
	const char	*nbr_ptr;

	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
	{
		print_error(ARG_NEG);
		return (NULL);
	}
	if (!is_digit(*str))
	{
		print_error(UNVALID_ARG);
		return (NULL);
	}
	nbr_ptr = str;
	return (nbr_ptr);
}

long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	str = valid_input(str);
	if (!str)
		return (-1);
	while (is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > INT_MAX)
	{
		print_error(ARG_BIG);
		result = -1;
	}
	return (result);
}

int	parse_input(t_settings *set, const char **argv)
{
	set->num_ph = (long)ft_atol(argv[1]);
	if (set->num_ph == -1)
		return (EXIT_FAILURE);
	if (set->num_ph == 0)
		return (print_error(NO_PHILO));
	set->tt_die = (long)ft_atol(argv[2]) * 1e3;
	set->tt_eat = (long)ft_atol(argv[3]) * 1e3;
	set->tt_sleep = (long)ft_atol(argv[4]) * 1e3;
	if (set->tt_die == -1e3 || set->tt_eat == -1e3 || set->tt_sleep == -1e3)
		return (EXIT_FAILURE);
	if (set->tt_die < 6e4 || set->tt_eat < 6e4 || set->tt_sleep < 6e4)
		return (print_error(ARG_SMALL));
	if (argv[5])
	{
		set->max_meals = ft_atol(argv[5]);
		if (set->max_meals < 1)
			return (print_error(NO_MEALS));
	}
	else
		set->max_meals = -1;
	return (EXIT_SUCCESS);
}
