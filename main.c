
#include "philo.h"
#include <sys/time.h> 
int main(int argc, char const *argv[])
{
  (void)argc;
  (void)argv;
  const char *test[] = {"0", "5", "900", "200","250", "5"};
  t_settings *settings;
  settings = ft_calloc(1, sizeof(t_settings)); 

  if (argc == 5 || argc == 6)
      parse_argv(settings, argv);
write(1,"INICIO\n", 7);
//for testing
parse_argv(settings, test);

load_settings(settings, test);
create_mutexes(settings);
settings->start_simulation = false;//i used calloc, i should be  false already
gettimeofday(&settings->synchro_t, NULL);
set_threshold(settings);
create_philos(settings);

join_threads(settings);

exiting(settings, SUCCESS); 
return 0;
}
