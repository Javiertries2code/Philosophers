#include "../philo.h"
/*
The idea is that it cheacks the start simulation, for a inchronuous starting, same as
all alive, to quite, hence the data it should

◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

void *routine_ph(void *args)
{
    t_philo philo;
    struct timeval delay;
    philo = *(t_philo *)args;
    int *ret = malloc(sizeof(int));
     *ret = 2;
    // I cant use a mutex before, as the phile is created before
    // safe_mutex(philo.write_mtx, LOCK);

    // printf("Entering routinph [%ld]:\n*(t_philo *)args).thread_id = %ld\n ", philo.philo_id, (*(t_philo *)args).thread_id);
    // safe_mutex(philo.write_mtx, UNLOCK);

    safe_mutex(philo.time_mtx, LOCK);
    calculate_delay(&delay, philo.settings->synchro_t, philo.write_mtx);
    // safe_mutex(philo.write_mtx, LOCK);
    // printf(GREEN "[%ld] --- DELAYED= %ld\n" RESET, philo.philo_id, (long)delay.tv_usec);
    // safe_mutex(philo.write_mtx, UNLOCK);

    safe_mutex(philo.time_mtx, UNLOCK);
    // pthread_mutex_lock((*(t_philo *)args).t_general);

    // pthread_mutex_unlock(philo.t_general);
    safe_mutex(philo.write_mtx, LOCK);

    printf(CYAN "philo [%d] joins dinners\n" RESET, (int)philo.philo_id);
    safe_mutex(philo.write_mtx, UNLOCK);

    if (philo.philo_id % 2 == 0)
    {
        routine_even(&philo);
    }
    else
    {
        routine_odd(&philo);
    }
    safe_mutex(philo.write_mtx, LOCK);

    printf(PINK "philo [%d] LEAVING DINNER\n" RESET, (int)philo.philo_id);
    safe_mutex(philo.write_mtx, UNLOCK);
    //gotta find out how to exit, as exit quits the progra
   // exit(EXIT_SUCCESS);
    return ret;
}


void routine_even(t_philo *philo)
{
    // pthread_mutex_lock(philo->write_mtx);
    safe_mutex(philo->write_mtx, LOCK);

    printf(YELLOW "philo [%d]  is EVEN\n" RESET, (int)philo->philo_id);
    safe_mutex(philo->write_mtx, UNLOCK);
    sleep(1);
    // pthread_mutex_unlock(philo->write_mtx);

    (void)philo;
}

void routine_odd(t_philo *philo)
{
    // pthread_mutex_lock(philo->write_mtx);
    safe_mutex(philo->write_mtx, LOCK);

    printf(RED "philo [%d]  is ODD\n" RESET, (int)philo->philo_id);
    safe_mutex(philo->write_mtx, UNLOCK);
    sleep(1);

    // pthread_mutex_unlock(philo->write_mtx);
    (void)philo;
}

void check_deaths(t_settings *settings)
{
    int i;
     safe_mutex(settings->write_mtx, LOCK);

    printf(RED "Got into checking deaths\n\n" RESET);
    safe_mutex(settings->write_mtx, UNLOCK);

    while (ALL_ALIVE)
    {   safe_mutex(settings->write_mtx, LOCK);

    printf(RED "Got into checking deaths\n\n" RESET);
    safe_mutex(settings->write_mtx, UNLOCK);
        
        i = 0;
        safe_mutex(settings->t_status_mtx, LOCK);
        while (settings->num_philosophers > i)
        {
            if (settings->philo_status[i] == ONE_DIED)
                settings->funeral = ONE_DIED;
            if (settings->philo_status[i] == FULL)
                settings->all_full--;
            i++;
        }
        safe_mutex(settings->t_status_mtx, UNLOCK);
        usleep(100000);
    
    }
}
