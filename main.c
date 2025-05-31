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
	usleep(30);
	create_assitants(set);
	join_threads(set);
	exiting(set, NULL);
	return (ret);
}
