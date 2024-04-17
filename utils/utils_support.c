#include "../philo.h"


/**
 * @brief support function to read returned results
 *
 * @param settings
 */
void support_read_returns(t_settings *settings)
{
    int i;

    i = -1;
    while (settings->num_philosophers > ++i)
    {
        write(1, "read returns\n", 13);

        printf("philo [%ld]return_status = %d\n", settings->philosophers[i].philo_id, (int)((settings->return_status[i][0])));
        //printf("philo [%ld]return_status = %d\n",settings->philosophers[i].philo_id ,((settings->philosophers[i].status[0])));

    }
}

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

void write_function(t_settings *settings, char *str)
{
    safe_mutex(settings->t_write_mtx, LOCK);
    write(1, &str, ft_strlen(str));
    safe_mutex(settings->t_write_mtx, UNLOCK);
}
