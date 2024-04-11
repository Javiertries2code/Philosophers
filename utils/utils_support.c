#include "../philo.h"

/**
 * @brief this is a support functio to check if inputs were set
 *
 * @param settings
 */
void print_data(t_settings *settings, char *str)
{
  printf("\n%s\n", str);

  for (long int i = 0; i < settings->num_philosophers; i++)
  {
    if (&settings->philosophers[i] != NULL ||  settings->philosophers[i].philo_id != 0)
    {
      // printf("ettings->philosophers[%ld]->fork_id = %ld\n\n", i,
      //        settings->philosophers[i].philo_id);
    }
    if (&settings->mutexes[i] != NULL)
      
      write(1, "the mutex was set\n", 19);
    else
      write(1, "the mutex is null", 18);
  }
}