#include "../philo.h"
/**
 * @brief here the args are parsed, and if all good
 * it  call loads the settings struct
 * @see oad_settings
 * @param settings struct with general info common to every users
 * @param argv well! Our old good friend argv
 */
void parse_argv(t_settings *settings, char *argv[])
{    write(1,"into parseargv\n",16);

    settings = ft_calloc(1, sizeof(t_settings)); 
    load_settings(settings, argv);
}

//pending to make atoi and atol
/**
 * @brief Construct a new load settings object
 * 
 * @param setti
 * ngs 
 * @param argv 
 */
void load_settings(t_settings *settings, char **argv)
{
    write(1,"into load setting\n",18);
printf("%s %s %s %s \n", argv[1], argv[2], argv[3], argv[4]);
printf("%ld %ld %ld %ld \n", atol(argv[1]), atol(argv[2]), atol(argv[3]), atol(argv[4]));
    settings->num_philosophers = atol(argv[1]);
    settings->time_to_die = atol(argv[2]);
    settings->time_to_eat = atol(argv[3]);
    settings->time_to_sleep = atol(argv[4]);
    // if(argv[5] != NULL)
    //     settings->max_meals = atol(argv[5]);
    // else
    //     settings->max_meals = 0;
    write(1,"some load setting\n",18);

    settings->tenedores = ft_calloc(settings->num_philosophers, sizeof(t_fork ));
    //as in the struct  is defined like a t_philo* not tphilo**
   settings->philosophers = ft_calloc(settings->num_philosophers, sizeof(t_philo ));
    create_mutexes(settings);
    create_forks( settings);
}

void create_mutexes(t_settings *settings){
  int i;

    i = 0;
    settings->mutexes = (pthread_mutex_t *)ft_calloc(settings->num_philosophers, sizeof(pthread_mutex_t));

  while(i < (int)(settings->num_philosophers))
    {  
        pthread_mutex_init(&settings->mutexes[i], NULL);
    i++;
}
}
 void create_forks( t_settings *settings )
 {    write(1,"into create forks\n",19);

    int i;

    i = 0;
  while(i < (int)(settings->num_philosophers))
    {  
        settings->tenedores[i].fork_id = i+1;
    i++;
    }
  
   create_philos(settings);
 }

 void create_philos(t_settings *settings){

    long int i;
  
    i = 0;

  while(i < (settings->num_philosophers))
    {       
        settings->philosophers[i].philo_id = i + 1;   
        settings->philosophers[i].time_to_die = settings->time_to_die;
        settings->philosophers[i].time_to_eat = settings->time_to_eat;
        settings->philosophers[i].time_to_sleep = settings->max_meals;
        settings->philosophers[i].fork_next = &(settings->tenedores[i]);
        if (i == 0)
            settings->philosophers[i].fork_prev = &(settings->tenedores[settings->num_philosophers]);
        else
            settings->philosophers[i].fork_prev = &(settings->tenedores[i - 1]);
        i++;

    }
            print_data(settings);

}