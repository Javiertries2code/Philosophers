
#include "philo.h"
#include <sys/time.h> 
int main(int argc, char const *argv[])
{
  (void)argc;
  (void)argv;
  const char *test[] = {"0", "5", "800", "200","250" "5"};
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
create_philos(settings);

//pthread_mutex_lock(settings->t_time_mtx);
gettimeofday(&settings->synchro_t, NULL);
//pthread_mutex_lock(settings->t_time_mtx);

printf("main = %ld  main",settings->synchro_t.tv_usec);

settings->start_simulation = true;
settings->all_alive = true;
join_threads(settings);
//exiting(settings, SUCCESS);
  
return 0;
}
