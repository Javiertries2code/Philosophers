
#include "philo.h"
#include <sys/time.h>
int main(int argc, char const *argv[])
{
  (void)argc;
  (void)argv;


  const char *test[] = {"0", "5", "900", "200", "250", "5"};
  t_settings *settings;
  settings = ft_calloc(1, sizeof(t_settings));

  if (argc == 5 || argc == 6)
    parse_argv(settings, argv);
  write(1, "INICIO\n", 7);
  // for testing
  if (argv == NULL)
    parse_argv(settings, test);
  else
    parse_argv(settings, argv);

  load_settings(settings, test);
  create_mutexes(settings);
  create_philos(settings);
  
  join_threads(settings);

  //support_read_returns(settings);

  //  i = 0;
  //   while (settings->num_philosophers > i++)
  //       pthread_join(settings->philosophers[i].thread_id, NULL);
  //sleep(2);
  // if (settings->all_full == 0)
  //           exit(EXIT_SUCCESS);
  //exiting(settings, SUCCESS);
  //i could actually catch the return
  return 0;
}
