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
     settings->max_meals = NO_MAX_MEALS;
      if (argv[5] != NULL)
        settings->max_meals = atol(argv[5]);
    gettimeofday(&settings->synchro_t, NULL);
    set_threshold(settings);

    settings->philo_status = (int *)ft_calloc(settings->num_philosophers, sizeof(int));
    settings->return_status = (int **)ft_calloc(settings->num_philosophers, sizeof(int *));

    // if (argv[5] != NULL)
    //     settings->max_meals = atol(argv[5]);
    // else
    //     settings->max_meals = NO_MAX_MEALS;
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
    settings->t_common_status_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->t_maitre_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->time_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    ////////////
    //WEIRD AS FUCK 
    /*
    IT DOESNT SEEM TO CREATE NUM-PHILOSOFER GAPS FOR THE MUTEXES, recurrent probelm of allowing
    only 4 out of 5 philos, when blocking status in eating, the fail is experienced in staus mtx, but in case
    of i added the +1 in all mallocs*/
    /////
    settings->mutexes = (pthread_mutex_t *)ft_calloc(settings->num_philosophers, sizeof(pthread_mutex_t));
    settings->status_mtx = (pthread_mutex_t *)ft_calloc(settings->num_philosophers , sizeof(pthread_mutex_t ));

    //it fails if not added +1
    
    settings->meal_mtx = (pthread_mutex_t *)ft_calloc(settings->num_philosophers , sizeof(pthread_mutex_t));
    
    while (i < (int)(settings->num_philosophers))
    {
        safe_mutex(&settings->mutexes[i], INIT);
      
        //safe_mutex(&settings->status_mtx[i], INIT);

        //trying with 0 instead of the one ahead
        safe_mutex(&settings->status_mtx[i], INIT);
        safe_mutex(&settings->meal_mtx[i], INIT);

        i++;
    }
    safe_mutex(settings->t_write_mtx, INIT);
    safe_mutex(settings->time_mtx, INIT);
    safe_mutex(settings->t_maitre_mtx, INIT);
    safe_mutex(settings->t_common_status_mtx, INIT);
}

void create_maitre(t_settings *settings)
{
    t_maitre *maitre;

    maitre = ft_calloc(1, sizeof(t_maitre));
    settings->maitre = maitre;
    maitre->settings = settings;
    maitre->meal_mtx = settings->meal_mtx;
    maitre->status_mtx = settings->status_mtx;
    maitre->meal_mtx = settings->meal_mtx;
    maitre->write_mtx = settings->t_write_mtx;
    maitre->num_philosophers = settings->num_philosophers;
    maitre->philosophers = settings->philosophers;
    maitre->return_status = settings->return_status;
    maitre->time_mtx = settings->time_mtx;

    //Possible data races, as all  threads point here, no to change it, but it will be changed after set up
    //time mutex migh be of an interes
maitre->threshold = settings->threshold;
    maitre->synchro_t  = get_time(&settings->synchro_t, CHANGE, MILISECONDS);

    pthread_create(&maitre->th_maitre, NULL, &routine_maitre, (void *)&settings->maitre[0]);
    //settings->philosophers = ft_calloc(settings->num_philosophers, sizeof(t_philo));
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
    settings->philosophers = ft_calloc(settings->num_philosophers, sizeof(t_philo));

    //settings->philosophers = ft_calloc(settings->num_philosophers, sizeof(t_philo));
    //MOVED TO LOAD SETTINGS TO CUT LINES.
    i = 0;
    while (i < settings->num_philosophers)
    {

        settings->philosophers[i].philo_id = i + 1;
        settings->philosophers[i].time_to_die = settings->time_to_die;
        settings->philosophers[i].time_to_eat = settings->time_to_eat;
        settings->philosophers[i].time_to_sleep = settings->time_to_sleep;
        settings->philosophers[i].num_philosophers = settings->num_philosophers;
        settings->philosophers[i].settings = settings;
        settings->philosophers[i].max_meals = settings->max_meals;
        
        // mtexes
        settings->philosophers[i].t_write_mtx = settings->t_write_mtx;
        settings->philosophers[i].time_mtx = settings->time_mtx;
        settings->philosophers[i].t_common_status_mtx = &settings->t_common_status_mtx[i];
        // timing
        settings->philosophers[i].threshold = settings->threshold;
        //settings->philosophers[i].synchro_t = get_time(&settings->synchro_t, CHANGE, MILISECONDS);
        settings->philosophers[i].synchro_t = get_time(&settings->synchro_t, CHANGE, MILISECONDS);
        // mutexes: each pointer each one

        //iused 0 instead of one to try
        //settings->philosophers[i].status_mtx = &settings->status_mtx[i];

        settings->philosophers[i].status_mtx = settings->status_mtx;

        settings->philosophers[i].meal_mtx = &settings->meal_mtx[i];
        //access own retunr status
        settings->return_status[i] = (int *)ft_calloc(1, sizeof(int));

        //////asgfsadfgsadsagfda
        settings->philosophers[i].return_status = settings->return_status;
        settings->philosophers[i].fork_next = &settings->mutexes[i];
            
///ONLY UNTILL THE DELAY IN MAITRE IS SET UP
        settings->philosophers[i].last_meal = get_milisec(NULL, GET, MILISECONDS);
        
        if (i == 0)
            settings->philosophers[i].fork_prev = &(settings->mutexes[settings->num_philosophers -1]);
        else
            settings->philosophers[i].fork_prev = &(settings->mutexes[i - 1]);
            
        if (settings->philosophers[i].philo_id % 2 == 0)
        {
            settings->philosophers[i].first_fork = settings->philosophers[i].fork_next;
            settings->philosophers[i].second_fork = settings->philosophers[i].fork_prev;
        }
        else
        {
            settings->philosophers[i].second_fork = settings->philosophers[i].fork_next;
            settings->philosophers[i].first_fork = settings->philosophers[i].fork_prev;
        }
        // if (i == 0)
        //     settings->philosophers[i].fork_prev = &(settings->mutexes[settings->num_philosophers - 1]);
        // else
        //     settings->philosophers[i].fork_prev = &(settings->mutexes[i - 1]);
        pthread_create(&settings->philosophers[i].thread_id, NULL, &routine_ph, (void *)&settings->philosophers[i]);
        i++;
    }//check forks
    
   // set_forks(settings);
}

// void set_forks(t_settings *settings)
// {
//     long int i;

//     i = 0;
//     while (i < settings->num_philosophers)
//     {
//         if (i == 0)
//             settings->philosophers[i].fork_prev = &(settings->mutexes[settings->num_philosophers - 1]);
//         else
//             settings->philosophers[i].fork_prev = &(settings->mutexes[i - 1]);
            
//         if (settings->philosophers[i].philo_id % 2 == 0)
//         {
//             settings->philosophers[i].first_fork = settings->philosophers[i].fork_next;
//             settings->philosophers[i].second_fork = settings->philosophers[i].fork_prev;
//         }
//         else
//         {
//             settings->philosophers[i].second_fork = settings->philosophers[i].fork_next;
//             settings->philosophers[i].first_fork = settings->philosophers[i].fork_prev;
//         }
//         i++;
//     }
// }


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
     safe_mutex(settings->t_write_mtx, LOCK);
    
        //printf("philo [%d] joint with return_status = %d\n", i + 1, (int)((settings->return_status[i][0])));
     safe_mutex(settings->t_write_mtx, UNLOCK);

        if ((int)((settings->return_status[i][0])) == ONE_DIED)
        { // previous :    safe_mutex(settings->t_common_status_mtx, LOCK);
            j = -1;
            safe_mutex(&settings->status_mtx[i], LOCK);
            while (settings->num_philosophers > ++j)
                settings->return_status[j][0] = ONE_DIED;
            safe_mutex(&settings->status_mtx[i], UNLOCK);
        }
    }
//    write(1, "joint threads\n", 14);
}
