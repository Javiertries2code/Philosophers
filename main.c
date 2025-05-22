
#include "philo.h"
#include <sys/time.h>

int	main(int argc, char const *argv[])
{
	const char	*test[] = {"0", "9", "5500", "200", "250", "15"};
	t_settings	*settings;

	(void)argc;
	(void)argv;
	settings = ft_calloc(1, sizeof(t_settings));
	if (argc == 5 || argc == 6)
		parse_argv(settings, argv);
	// for testing
	if (argv == NULL)
		parse_argv(settings, test);
	else
		parse_argv(settings, argv);
	load_settings(settings, argv);
	create_mutexes(settings);
	create_philos(settings);
	if (TEST)
	{
		usleep(3500);
		create_maitre(settings);
	}
	join_threads(settings);
	exiting(settings, NULL);
	return (0);
}
