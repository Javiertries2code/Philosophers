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
  while (settings->num_ph > ++i)
  {
    write(1, "read returns\n", 13);

    printf("philo [%ld]return_status = %d\n", settings->philos[i].philo_id, (int)((settings->ret_st[i])));
    // printf("philo [%ld]return_status = %d\n",settings->philosophers[i].philo_id ,((settings->philosophers[i].status[0])));
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

  for (long int i = 0; i < settings->num_ph; i++)
  {
    if (&settings->philos[i] != NULL || settings->philos[i].philo_id != 0)
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

void check_mutex(t_settings *settings, char *mtx_name,pthread_mutex_t *mutex,char *mtx_name2, pthread_mutex_t *mutex2, t_philo *philo)
{

  safe_mutex(settings->t_write_mtx, LOCK);
  for (int i = 0; i < settings->num_ph; i++)
  {
    if (mutex && mutex2)
    {
      printf(CYAN "%s\n&mutex[%d] = %p\n" RESET,  mtx_name,i, &mutex[i]);
      printf(CYAN "%s\n&mutex2[%d] = %p\n" RESET,  mtx_name2,i, &mutex2[i]);
    }
    if (philo)
    {
      printf(YELLOW " philo->settings->status_mtx[%d] = %p\n"RESET,i, &philo->settings->st_mtx[i]);
      printf(WHITE "&philo->status-mtx[i] = %p\n" RESET, &philo->status_mtx[i]);
      printf(YELLOW "&settings->philosophers[i].status_mtx[settings->philosophers[i].philo_id -1]= %p\n" RESET, &settings->philos[i].status_mtx[settings->philos[i].philo_id -1]);
    }
    printf("\n\n");
  }
  safe_mutex(settings->t_write_mtx, UNLOCK);
}