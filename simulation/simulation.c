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

/**
 * @brief first points to the variable in settings int **return_status; 
 * is a array of ints, where the returned variable will be stored, 
 * if  death, it will be changed before returning, and after the join happens
 * all member of the array are set to ONEDIED. this is the signal for exiting
 * 
 * @param args 
 * @return void* 
 */
void *routine_ph(void *args)
{
    t_philo philo;
   // struct timeval delay;
    long delay_to_sync;
    philo = *(t_philo *)args;

    int *ret;
    ret = philo.settings->return_status[philo.philo_id - 1];
    //support printing status
    safe_mutex(philo.write_mtx, LOCK);
    printf(YELLOW "philo status  value = %d\n" RESET, *ret);
    safe_mutex(philo.write_mtx, UNLOCK);

    safe_mutex(philo.time_mtx, LOCK);
    //calculate_delay(&delay, philo.settings->synchro_t, philo.write_mtx);
    delay_to_syncro(&delay_to_sync, &philo.synchro_t, philo.write_mtx);
    precise_sleep(delay_to_sync, &philo.threshold);
    safe_mutex(philo.time_mtx, UNLOCK);
    //support printing, delay
    safe_mutex(philo.write_mtx, LOCK);
    printf(CYAN "philo [%d] joins dinners\n" RESET, (int)philo.philo_id);
   // printf(WHITE "delay.tv = %ld\n" RESET, (long)get_time(&delay,GET,MILISECONDS));
    printf(BLUE "ndelaying = %ld\n" RESET, delay_to_sync);
    printf(YELLOW "nthreshold = %ld\n" RESET, philo.threshold);
    //printf(YELLOW "nthreshold = %ld\n" RESET, (long)philo.settings->threshold);

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

    printf(PINK "philo [%d] LEAVING DINNER IN MAIN THREAD\n" RESET, (int)philo.philo_id);
    safe_mutex(philo.write_mtx, UNLOCK);

    return ret;
}

/**
 * @brief evaluates return_status, then it procceds with action, or quits
 * 
 * @param philo 
 */
int routine_even(t_philo *philo)
{
    
    while(true)
    {  // previous mutex status for all of them.  philo->settings->status_mtx;
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if(philo->settings->return_status[philo->philo_id -1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        //think();
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if(philo->settings->return_status[philo->philo_id -1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        //eat();
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if(philo->settings->return_status[philo->philo_id -1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        //take_nap(); this could simply be a preccise sleep(sleeping time);


    }

    // pthread_mutex_lock(philo->write_mtx);
    safe_mutex(philo->write_mtx, LOCK);
    printf(YELLOW "philo [%d]  is EVEN\n" RESET, (int)philo->philo_id);
    safe_mutex(philo->write_mtx, UNLOCK);
    sleep(1);
    // pthread_mutex_unlock(philo->write_mtx);

    (void)philo;
}

int routine_odd(t_philo *philo)
{      

      while(true)
    {  // previous mutex status for all of them.  philo->settings->status_mtx;
        
                

        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if(philo->settings->return_status[philo->philo_id -1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        //think();
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if(philo->settings->return_status[philo->philo_id -1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);
              

        //eat();
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if(philo->settings->return_status[philo->philo_id -1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);
                   

        //take_nap(); this could simply be a preccise sleep(sleeping time);


    }
    // pthread_mutex_lock(philo->write_mtx);
    safe_mutex(philo->write_mtx, LOCK);

    printf(RED "philo [%d]  is ODD\n" RESET, (int)philo->philo_id);
    safe_mutex(philo->write_mtx, UNLOCK);
    sleep(1);

    // pthread_mutex_unlock(philo->write_mtx);
    (void)philo;
}

// void check_deaths(t_settings *settings)
// {
//     int i;
//     safe_mutex(settings->write_mtx, LOCK);

//     printf(RED "Got into checking deaths\n\n" RESET);
//     safe_mutex(settings->write_mtx, UNLOCK);

//     while (ALL_ALIVE)
//     {
//         safe_mutex(settings->write_mtx, LOCK);

//         printf(RED "Got into checking deaths\n\n" RESET);
//         safe_mutex(settings->write_mtx, UNLOCK);

//         i = 0;
//         safe_mutex(settings->t_status_mtx, LOCK);
//         while (settings->num_philosophers > i)
//         {
//             if (settings->philo_status[i] == ONE_DIED)
//                 settings->funeral = ONE_DIED;
//             if (settings->philo_status[i] == FULL)
//                 settings->all_full--;
//             i++;
//         }
//         safe_mutex(settings->t_status_mtx, UNLOCK);
//         usleep(100000);
//     }
// }
