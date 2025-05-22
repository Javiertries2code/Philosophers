#include "../philo.h"

void parse_argv(t_settings *settings, const char *argv[])
{   

(void)settings;
(void)argv;

    
}


void load_settings(t_settings *settings, const char *argv[])
{
    settings->num_philosophers = ft_atol(argv[1]);
    settings->time_to_die = ft_atol(argv[2]);
    settings->time_to_eat = ft_atol(argv[3]);
    settings->time_to_sleep = ft_atol(argv[4]);
     settings->max_meals = NO_MAX_MEALS;
      if (argv[5] != NULL)
        settings->max_meals = ft_atol(argv[5]);
    gettimeofday(&settings->synchro_t, NULL);
    set_threshold(settings);
    settings->philo_status = (int *)ft_calloc(settings->num_philosophers, sizeof(int));
    settings->return_status = ft_calloc(settings->num_philosophers, sizeof(int));
    settings->printer = 0;
    settings->funeral = 0;
    settings->starting_time = 0;
    settings->all_full = settings->num_philosophers;
  }

