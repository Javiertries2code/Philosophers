
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
		ft_putstr_fd("Wrong input: Please enter:\n\t'./philo  " \
			"number_of_philosophers  time_to_die  time_to_eat  time_to_sleep" \
			"  [max_meals_per_philo]'.\n", STDERR_FILENO);
	else if (err_id == ARG_NEG)
		ft_putstr_fd("Arguments must be Positive.\n",
			STDERR_FILENO);
	else if (err_id == UNVALID_ARG)
		ft_putstr_fd("Enter a valid numeric positive value" \
			" argument.\n", STDERR_FILENO);
	else if (err_id == ARG_TOO_BIG)
		ft_putstr_fd("Arguments must be smaller than" \
			" MAX_INT.\n", STDERR_FILENO);
	else if (err_id == ARG_TOO_SMALL)
		ft_putstr_fd("Timing arguments must be greater than " \
			" than 60ms.\n", STDERR_FILENO);
	else if (err_id == NO_PHILO_ERROR)
		ft_putstr_fd("Number of philosophers must be over 0.\n", STDERR_FILENO);
	else if (err_id == O_MAX_MEALS)
		ft_putstr_fd("Meals must be greater than 0\n", STDERR_FILENO);
	else if (err_id == MALLOC_ERROR)
		ft_putstr_fd("Malloc failed.\n", STDERR_FILENO);
	
	return (err_id);
}

/*
 * This function prints an error msg on STDERR_FLENO given the str
 * and returns int EXIT_FAILURE.
 */
int	error_str(char	*str)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
