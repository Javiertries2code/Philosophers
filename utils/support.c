#include "../philo.h"


void print_data(t_settings *settings)
{
      for (long int i = 0; i < settings->num_philosophers; i ++)
   { printf("ettings->tenedores[%ld]->fork_id = %ld\n", i,
     settings->tenedores[i].fork_id);
     printf("ettings->philosophers[%ld]->fork_id = %ld\n\n", i,
     settings->philosophers[i].philo_id);}
}