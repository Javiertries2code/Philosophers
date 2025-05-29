
#include "philo.h"
#include <sys/time.h>

int	main(int argc, char const *argv[])
{
	const char	*test[] = {"0", "9", "5500", "200", "250", "15"};
	t_settings	*set;

	(void)argc;
	(void)argv;
	set = kloc(1, sizeof(t_settings));
	if (argc == 5 || argc == 6)
		parse_argv(set, argv);
	// for testing
	if (argv == NULL)
		parse_argv(set, test);
	else
		parse_argv(set, argv);
	load_settings(set, argv);
	
	create_mutexes(set);
	create_philos(set);
	create_assitant(set);
	//usleep(3500);
	//create_maitre(set);
	join_threads(set);
	exiting(set, NULL);
	return (0);
}
