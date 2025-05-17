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
    settings->return_status = ft_calloc(settings->num_philosophers, sizeof(int));
    settings->printer = 0;
    settings->funeral = 0;
   

    // if (argv[5] != NULL)
    //     settings->max_meals = atol(argv[5]);
    // else
    //     settings->max_meals = NO_MAX_MEALS;

   // printf("IN load_settings   \ntime_to_die = %ld\ntime_to_eat = %ld\n  time_to_sleep = %ld\n ",  settings->time_to_die,settings->time_to_eat , settings->time_to_sleep );
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
    settings->t_maitre_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->time_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->printer_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->funeral_mtx = ft_calloc(settings->num_philosophers, sizeof(pthread_mutex_t));
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
        safe_mutex(&settings->funeral_mtx[i], INIT);

        i++;
    }


    safe_mutex(settings->t_write_mtx, INIT);
    safe_mutex(settings->time_mtx, INIT);
    safe_mutex(settings->t_maitre_mtx, INIT);
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
    ///


    maitre->funeral = &(settings->funeral);
    maitre->funeral_mtx = settings->funeral_mtx;
    maitre->printer = &(settings->printer);
    maitre->printer_mtx = settings->printer_mtx;

   
maitre->threshold = settings->threshold;
    maitre->synchro_t  = get_time(&settings->synchro_t, CHANGE, MILISECONDS);

    pthread_create(&maitre->th_maitre, NULL, &routine_maitre, (void *)&settings->maitre[0]);
}
static void	init_philo_data(t_settings *settings, long int i)
{
	t_philo	*philo;

	philo = &settings->philosophers[i];
	philo->philo_id = i + 1;
	philo->time_to_die = settings->time_to_die;
	philo->time_to_eat = settings->time_to_eat;
	philo->time_to_sleep = settings->time_to_sleep;
	philo->num_philosophers = settings->num_philosophers;
	philo->settings = settings;
	philo->max_meals = settings->max_meals;
	philo->t_write_mtx = settings->t_write_mtx;
	philo->time_mtx = settings->time_mtx;
	philo->threshold = settings->threshold;
	philo->synchro_t = get_time(&settings->synchro_t, CHANGE, MILISECONDS);
    philo->status_mtx = &settings->status_mtx[i];
	philo->meal_mtx = &settings->meal_mtx[i];
	settings->philosophers[i].return_status = &settings->return_status[i];

	philo->fork_next = &settings->mutexes[i];
	philo->last_meal = get_milisec(NULL, GET, MILISECONDS);

    //////
    philo->funeral = &(settings->funeral);
    philo->funeral_mtx = settings->funeral_mtx;
    philo->printer = &(settings->printer);
    philo->printer_mtx = settings->printer_mtx;
}

static void	assign_forks(t_settings *settings, long int i)
{
	t_philo	*philo;

	philo = &settings->philosophers[i];
	if (i == 0)
		philo->fork_prev = &settings->mutexes[settings->num_philosophers - 1];
	else
		philo->fork_prev = &settings->mutexes[i - 1];
	if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = philo->fork_next;
		philo->second_fork = philo->fork_prev;
	}
	else
	{
		philo->second_fork = philo->fork_next;
		philo->first_fork = philo->fork_prev;
	}
}

void	create_philos(t_settings *settings)
{
	long int	i;

	i = 0;
	settings->philosophers = ft_calloc(settings->num_philosophers, sizeof(t_philo));
	while (i < settings->num_philosophers)
	{

		init_philo_data(settings, i);
		assign_forks(settings, i);
		pthread_create(&settings->philosophers[i].thread_id,
			NULL, &routine_ph, (void *)&settings->philosophers[i]);
		i++;
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
    //int j;

    i = -1;
    pthread_join(settings->maitre->th_maitre, NULL);
///TEST
    safe_mutex(settings->t_write_mtx, LOCK);
    printf("%sjoin_threads %ld maitre %s\n", CYAN,
        (get_milisec() - settings->starting_time),
         RESET);
    safe_mutex(settings->t_write_mtx, UNLOCK);

    while (settings->num_philosophers > ++i)
    {
        void *ret;
        pthread_join(settings->philosophers[i].thread_id, &ret);
     
    }
//    write(1, "joint threads\n", 14);
}
