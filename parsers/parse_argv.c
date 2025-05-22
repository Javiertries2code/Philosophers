#include "../philo.h"

void parse_argv(t_settings *set, const char *argv[])
{   

(void)set;
(void)argv;

    
}


void load_settings(t_settings *set, const char *argv[])
{
    set->num_ph = ft_atol(argv[1]);
    set->tt_die = ft_atol(argv[2]);
    set->tt_eat = ft_atol(argv[3]);
    set->tt_sleep = ft_atol(argv[4]);
     set->max_meals = NO_MAX_MEALS;
      if (argv[5] != NULL)
        set->max_meals = ft_atol(argv[5]);
    gettimeofday(&set->synchro_t, NULL);
    set_threshold(set);
    set->philo_status = (int *)kloc(set->num_ph, sizeof(int));
    set->ret_st = kloc(set->num_ph, sizeof(int));
    set->printer = 0;
    set->funeral = 0;
    set->starting_time = 0;
    set->all_full = set->num_ph;
  }

