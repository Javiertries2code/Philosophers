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
    settings->anyone_death = ALL_ALIVE;
    if(argv[5] != NULL)
        settings->max_meals = atol(argv[5]);
    else
        settings->max_meals = NO_MAX_MEALS ;

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

    write(1, "in create mutexes\n", 18);

    i = 0;
    settings->t_general = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->time_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->mutexes = (pthread_mutex_t *)ft_calloc(settings->num_philosophers, sizeof(pthread_mutex_t));
    settings->write_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    while (i < (int)(settings->num_philosophers))
    {
        pthread_mutex_init(&settings->mutexes[i], NULL);

        i++;
    }
    pthread_mutex_init(settings->write_mtx, NULL);
    pthread_mutex_init(settings->time_mtx, NULL);
    pthread_mutex_init(settings->t_general, NULL);
}

void create_philos(t_settings *settings)
{

    long int i;

    i = 0;
    write(1, "in create philosos\n", 18);
    printf(RED " num philold %ld\n" RESET, settings->num_philosophers);
    settings->philosophers = ft_calloc(settings->num_philosophers, sizeof(t_philo));

    // pthread_mutex_lock(settings->t_general);
    while (i < (settings->num_philosophers))
    {
        settings->philosophers[i].philo_id = i + 1;
        /// it seems that it points to 0 in simulation

        // pthread_create(&settings->philosophers[i].thread_id, NULL, &routine_ph, (void *)&settings->philosophers[i]);

        settings->philosophers[i].time_to_die = settings->time_to_die;
        settings->philosophers[i].time_to_eat = settings->time_to_eat;
        settings->philosophers[i].time_to_sleep = (settings->max_meals);
        settings->philosophers[i].fork_next = &settings->mutexes[i];
        settings->philosophers[i].settings = settings;
        settings->philosophers[i].write_mtx = settings->write_mtx;
        settings->philosophers[i].time_mtx = settings->time_mtx;
        if (i == 0)
            settings->philosophers[i].fork_prev = &(settings->mutexes[settings->num_philosophers]);
        else
            settings->philosophers[i].fork_prev = &(settings->mutexes[i - 1]);

        pthread_create(&settings->philosophers[i].thread_id, NULL, &routine_ph, (void *)&settings->philosophers[i]);
        i++;
    }

    // pthread_mutex_unlock(settings->t_general);
}
/**
 * @brief Joins threads, execution wont proceed untill all of them are joint
 *
 * @param settings
 */
void join_threads(t_settings *settings)
{
    int i;

    i = 0;
    while (settings->num_philosophers > i++)
        pthread_join(settings->philosophers[i].thread_id, NULL);
}