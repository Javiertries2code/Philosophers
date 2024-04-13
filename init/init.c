#include "../philo.h"
// pending to make atoi and atol
/**
 * @brief it loads the input data from argv to the common data struct settings
 * ******ATOL IS PENDING TO BE CODED YET, USING LIBRARY SO FAR****
 * it calls create_mutextes on completion

 * @see create_mutexes()
 * @param settings
 * ngs
 * @param argv
 */
void load_settings(t_settings *settings, const char *argv[])
{
    settings->num_philosophers = atol(argv[1]);
    settings->time_to_die = atol(argv[2]);
    settings->time_to_eat = atol(argv[3]);
    settings->time_to_sleep = atol(argv[4]);
    settings->all_full = settings->num_philosophers;

    settings->philo_status = (int *)ft_calloc(settings->num_philosophers, sizeof(int));
    settings->return_status = (int **)ft_calloc(settings->num_philosophers, sizeof(int *));
    if (argv[5] != NULL)
        settings->max_meals = atol(argv[5]);
    else
        settings->max_meals = NO_MAX_MEALS;
}
/**
 * @brief Allocates memoryy for mutexes and initialize them
 * debug cheack is to be eliminates
 *
 *
 * @param settings
 */
void create_mutexes(t_settings *settings)
{
    int i;

    i = 0;
    settings->t_maitre_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->t_funeral_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->time_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->mutexes = (pthread_mutex_t *)ft_calloc(settings->num_philosophers, sizeof(pthread_mutex_t));
    settings->write_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->t_status_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    while (i < (int)(settings->num_philosophers))
    {
        safe_mutex(&settings->mutexes[i], INIT);
        i++;
    }
    safe_mutex(settings->write_mtx, INIT);
    safe_mutex(settings->time_mtx, INIT);
    safe_mutex(settings->t_funeral_mtx, INIT);
    safe_mutex(settings->t_maitre_mtx, INIT);
    safe_mutex(settings->t_status_mtx, INIT);
}

void create_philos(t_settings *settings)
{
    long int i;

    i = 0;
    settings->philosophers = ft_calloc(settings->num_philosophers, sizeof(t_philo));
    while (i < settings->num_philosophers)
    {
        settings->philosophers[i].philo_id = i + 1;
        settings->philosophers[i].time_to_die = settings->time_to_die;
        settings->philosophers[i].time_to_eat = settings->time_to_eat;
        settings->philosophers[i].time_to_sleep = settings->time_to_sleep;
        settings->philosophers[i].fork_next = &settings->mutexes[i];
        settings->philosophers[i].settings = settings;
        settings->philosophers[i].write_mtx = settings->write_mtx;
        settings->philosophers[i].time_mtx = settings->time_mtx;
        settings->philosophers[i].t_status_mtx = settings->t_status_mtx;
        if (i == 0)
            settings->philosophers[i].fork_prev = &(settings->mutexes[settings->num_philosophers - 1]);
        else
            settings->philosophers[i].fork_prev = &(settings->mutexes[i - 1]);
        settings->return_status[i] = (int *)ft_calloc(1, sizeof(int));
        pthread_create(&settings->philosophers[i].thread_id, NULL, &routine_ph, (void *)&settings->philosophers[i]);
        i++;
    }
}

 void read_returns(t_settings *settings){
    int i;

    i = -1;
  while (settings->num_philosophers > ++i)
    {    write(1, "read returns\n", 13);

       printf("philo [%d]return_status = %d\n", i + 1, (int)((settings->return_status[i][0])));

    }
 }

void join_threads(t_settings *settings)
{
    int i;

    i = -1;
    while (settings->num_philosophers > ++i)
    {
        //settings->return_status[i] = (int *)ft_calloc(1, sizeof(int));
        pthread_join(settings->philosophers[i].thread_id, (void **)&settings->return_status[i]);
        printf("philo [%d] joint with return_status = %d\n", i + 1, (int)((settings->return_status[i][0])));

        sleep(1);
    }
          write(1, "joint threads\n", 14);

}
/**
 * @brief it makes a loop where, if a max meals was given, and it found all fed
 * then SUCCESS. Else, loops for any dead philo and updates th funeral to DIED, if so.
 * it counts for FULL philos, again if max meal is given
 * @param settings
 */
