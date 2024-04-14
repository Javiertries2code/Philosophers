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
    gettimeofday(&settings->synchro_t, NULL);
    set_threshold(settings);



    settings->philo_status = (int *)ft_calloc(settings->num_philosophers, sizeof(int));
    settings->return_status = (int **)ft_calloc(settings->num_philosophers, sizeof(int *));
    if (argv[5] != NULL)
        settings->max_meals = atol(argv[5]);
    else
        settings->max_meals = NO_MAX_MEALS;
}
/**
 * @brief Allocates memoryy for mutexes and initialize them
 * in the loop it crreates mutexes for each fork, and for each return status, as each and every
 * philo access it own return status.
 * hence, looping return_mutex[philo.id] will speed up the reading.
 *
 *
 * @param settings
 */
void create_mutexes(t_settings *settings)
{
    int i;

    i = 0;
    settings->t_write_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->t_status_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->t_maitre_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->time_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    //arr mtxs
    settings->mutexes = (pthread_mutex_t *)ft_calloc(settings->num_philosophers, sizeof(pthread_mutex_t));
    settings->status_mtx = (pthread_mutex_t *)ft_calloc(settings->num_philosophers, sizeof(pthread_mutex_t));
    settings->meal_mtx = (pthread_mutex_t *)ft_calloc(settings->num_philosophers, sizeof(pthread_mutex_t));
    

    while (i < (int)(settings->num_philosophers))
    {
        safe_mutex(&settings->mutexes[i], INIT);
        safe_mutex(&settings->status_mtx[i], INIT);
        safe_mutex(&settings->meal_mtx[i], INIT);

        i++;
    }
    safe_mutex(settings->t_write_mtx, INIT);
    safe_mutex(settings->time_mtx, INIT);
    safe_mutex(settings->t_maitre_mtx, INIT);
    safe_mutex(settings->t_status_mtx, INIT);
}

void create_maitre(t_settings *settings)
{
    t_maitre *maitre;
    
    settings->maitre = ft_calloc(1, sizeof(t_maitre));
    maitre = settings->maitre;
    maitre->meal_mtx = settings->meal_mtx;
    maitre->status_mtx = settings->status_mtx;
    maitre->meal_mtx = settings->meal_mtx;
    maitre->write_mtx = settings->t_write_mtx;
    maitre->num_philosophers = settings->num_philosophers;
    maitre->philosophers = settings->philosophers;
    maitre->return_status = settings->return_status;
    pthread_create(&maitre->th_maitre, NULL, &routine_maitre, (void *)&settings->maitre[0]);


}



/**
 * @brief Create a philos objectfor every philo, it provides the dta loaded
 * so it doesnt need to check the common struc. Also assign an indiddual mutex for each 
 * philo in 
 * 
 * @param settings 
 */
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
        settings->philosophers[i].num_philosophers = settings->num_philosophers;
        settings->philosophers[i].settings = settings;
        settings->philosophers[i].last_meal = get_time(&settings->synchro_t, CHANGE, MILISECONDS) + SAND_CLOCK;
        //mtexes
        settings->philosophers[i].t_write_mtx = settings->t_write_mtx;
        settings->philosophers[i].time_mtx = settings->time_mtx;
        settings->philosophers[i].t_status_mtx = settings->t_status_mtx;
        settings->philosophers[i].threshold = settings->threshold;
        settings->philosophers[i].synchro_t =get_time(&settings->synchro_t, CHANGE, MILISECONDS); 
        //each pointer each one
        settings->philosophers[i].fork_next= &settings->mutexes[i];
        settings->philosophers[i].status_mtx = &settings->status_mtx[i];
        settings->philosophers[i].meal_mtx = &settings->meal_mtx[i];

        if (i == 0)
            settings->philosophers[i].fork_prev = &(settings->mutexes[settings->num_philosophers - 1]);
        else
            settings->philosophers[i].fork_prev = &(settings->mutexes[i - 1]);
        settings->return_status[i] = (int *)ft_calloc(1, sizeof(int));
        pthread_create(&settings->philosophers[i].thread_id, NULL, &routine_ph, (void *)&settings->philosophers[i]);
        i++;
    }
}
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

        printf("philo [%d]return_status = %d\n", i + 1, (int)((settings->return_status[i][0])));
    }
}
/**
 * @brief When joining it  reads the returned argunment, 
 * (now that i think it should be mutexed also when writing it a new status)
 * if it evaluates the status  to ONEDIED. it sets the whole array to ONEDIED, what will be continously 
 * check in the thread. not need to malloc there, as it comes built from init.
 * 
 * @param settings 
 */
void join_threads(t_settings *settings)
{
    int i;
    int j;

    i = -1;

    while (settings->num_philosophers > ++i)
    {
        // settings->return_status[i] = (int *)ft_calloc(1, sizeof(int));
        pthread_join(settings->philosophers[i].thread_id, (void **)&settings->return_status[i]);
        printf("philo [%d] joint with return_status = %d\n", i + 1, (int)((settings->return_status[i][0])));

        if ((int)((settings->return_status[i][0])) == ONE_DIED)
        {//previous :    safe_mutex(settings->t_status_mtx, LOCK);
            j = -1;
            safe_mutex(&settings->status_mtx[i], LOCK);
            while (settings->num_philosophers > ++j)
                settings->return_status[j][0] = ONE_DIED;
            safe_mutex(&settings->status_mtx[i], UNLOCK);
        }
    }
    write(1, "joint threads\n", 14);
}
/**
 * @brief it makes a loop where, if a max meals was given, and it found all fed
 * then SUCCESS. Else, loops for any dead philo and updates th funeral to DIED, if so.
 * it counts for FULL philos, again if max meal is given
 * @param settings
 */
