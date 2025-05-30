
#include "philo.h"
#include <sys/time.h>

int	main(int argc, char const *argv[])
{

	int ret;

	ret = 0;
	if (argc <= 1 || argc > 6)
		return (0);
	t_settings	*set;

	(void)argc;
	(void)argv;
	set = kloc(1, sizeof(t_settings));

		if (argc == 5 || argc == 6)
			ret = parse_input(set, argv);
		

	 if(ret)
	 	return (ret);
	
	
	load_settings(set, argv);
	create_mutexes(set);
	create_philos(set);
	create_assitant(set);
	//usleep(3500);
	//create_maitre(set);
	join_threads(set);
	exiting(set, NULL);
	return (ret);
}
