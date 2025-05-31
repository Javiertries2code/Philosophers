#include "philo.h"
#include <sys/time.h>

int	main(int argc, char const *argv[])
{
	int			ret;
	t_settings	*set;

	ret = SUCCESS;
	if (argc <= 1 || argc > 6)
		return (0);
	set = kloc(1, sizeof(t_settings));
	if (argc == 5 || argc == 6)
		ret = parse_input(set, argv);
	if (ret)
		return (ret);
	load_settings(set, argv);
	create_mutexes(set);
	create_philos(set);
	create_assitant(set);
	join_threads(set);
	exiting(set, NULL);
	return (ret);
}
