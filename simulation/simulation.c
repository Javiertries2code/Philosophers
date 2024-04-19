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
 * @brief it firstlo locks all the return status for each philo,
 * then updates the statu to  ONEDIED
 * unlocks them all
 *
 * @param maitre
 */
void set_all_died(t_maitre *maitre)
{
    int i;

    i = 0;
    // locks all for speed
    while (maitre->num_philosophers > i)
    {
        safe_mutex(&maitre->status_mtx[i], LOCK);
        i++;
    }
    // updates all
    i = 0;
    while (maitre->num_philosophers > i)
    {
        maitre->return_status[i][0] = ONE_DIED;
        i++;
    }
    // unlocks all for speed

    i = 0;
    while (maitre->num_philosophers > i)
    {
        safe_mutex(&maitre->status_mtx[i], UNLOCK);
        i++;
    }
}
/**
 * @brief eternal loop untill it reaturns
 * Locks status[i]  and check if all philos status != FULL (status DEATH is not posible),
 *  as the maitre  would RETURN after anyone dies and overwrite the status to DEATH.
 * it unluck before set_all dead to avoid deathlocks
 *
 * it writes later the "DIED " message when the status was already changed
 * in the routine, it will lock WRITE, adn then lock status, so it wouldnt write a new ongoing action
 * if the status was already changed.
 *
 * @param args
 * @return void*
 */

// test
void *routine_maitre(void *args)
{
    t_maitre maitre;
    long int i;

    maitre = *(t_maitre *)args;

    while (true)
    {
        i = 0;
        while (maitre.num_philosophers > i)
        { 
            safe_mutex(&maitre.status_mtx[i], LOCK);
            // printf("IN MAITRE LOOP after mutex \n");

            if (maitre.return_status[i][0] != FULL)
            {
               // printf(YELLOW " iNSECOND LOOP &maitre.status_mtx[%ld]  = %p\n" RESET, i, &maitre.status_mtx[i]);
                printf(WHITE " \nXXXXXTIME_LEFT (&(maitre.philosophers[%ld])  =%ld \n"RESET,i, time_left(&(maitre.philosophers[i])));
                printf(WHITE " \nmaitre.philosophers[i].last_meal[%ld])  =%ld \n"RESET,i, maitre.philosophers[i].last_meal);

                if (time_left(&(maitre.philosophers[i]))  <= 0)
                {
                    maitre.return_status[i][0] = ONE_DIED;
                    safe_mutex(&maitre.status_mtx[i], UNLOCK);

                    set_all_died(&maitre);
                    safe_mutex(maitre.write_mtx, LOCK);
                    printf(CYAN "% ld %ld died\n" RESET, get_time(NULL, GET, MILISECONDS), (long)maitre.philosophers[i].philo_id);
                    safe_mutex(maitre.write_mtx, UNLOCK);
                    return NULL;
                }
              //  printf(BLUE " BEFORE UNLOCK !=FULL &maitre.status_mtx[%ld]  = %p\n"RESET,i, &maitre.status_mtx[i]);

                safe_mutex(&maitre.status_mtx[i], UNLOCK);
            }
            else if (maitre.return_status[i][0] == FULL)
            {
                safe_mutex(maitre.write_mtx, LOCK);
                printf(CYAN "% ld %ld FULL IN MAITRE\n" RESET, get_time(NULL, GET, MILISECONDS), (long)maitre.philosophers[i].philo_id);
                safe_mutex(maitre.write_mtx, UNLOCK);

                printf(YELLOW " BEFORE UNLOCK ==FULL &maitre.status_mtx[%ld]  = %p\n" RESET, i, &maitre.status_mtx[i]);

                safe_mutex(&maitre.status_mtx[i], UNLOCK);
            }
            i++;
        }
    }
}

//         if (time_left_die <= 0)
//         { // NECESARIA, IMPRIME MUERTOS
//             safe_mutex(maitre.write_mtx, LOCK);
//             printf(YELLOW "% ld %ld died\n" RESET, get_time(NULL, GET, MILISECONDS), (long)maitre.philosophers[i].philo_id);
//             safe_mutex(maitre.write_mtx, UNLOCK);
//             i = 0;
//             while (maitre.num_philosophers > i)
//             {
//                 // safe_mutex(maitre.status_mtx[, LOCK); this one worked
//                 safe_mutex(&maitre.status_mtx[i], LOCK);
//                 maitre.return_status[i][0] = ONE_DIED;
//                 safe_mutex(&maitre.status_mtx[i], UNLOCK);
//                 // safe_mutex(maitre.write_mtx, LOCK);
//                 // printf(YELLOW "philo[%ld] maitre.return_status[i][0]= %d \n" RESET, (i + 1), maitre.return_status[i][0]);
//                 // safe_mutex(maitre.write_mtx, UNLOCK);
//                 i++;
//             }
//             return (NULL);
//         }
//         i++;
//     }
// }
// return (NULL);
// }
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
    // support printing status
    safe_mutex(philo.t_write_mtx, LOCK);
    printf(YELLOW "[%ldJOINING DINNER:\n philo status  value = %d\n" RESET, philo.philo_id, *ret);
    safe_mutex(philo.t_write_mtx, UNLOCK);

    safe_mutex(philo.time_mtx, LOCK);
    // NOT IN USE: calculate_delay(&delay, philo.settings->synchro_t, philo.t_write_mtx);
    delay_to_sync = delay_to_syncro(&delay_to_sync, &philo.synchro_t, philo.t_write_mtx);
    // safe_mutex(philo.t_write_mtx, LOCK);
    // printf(RED "[delay_to_sync =  %ld\n philo.threshold = %ld\n" RESET, delay_to_sync, philo.threshold);
    // safe_mutex(philo.t_write_mtx, UNLOCK);
    precise_sleep(delay_to_sync, &philo.threshold);
    philo.last_meal = get_milisec(NULL, GET, MILISECONDS);

    safe_mutex(philo.time_mtx, UNLOCK);
    // support printing, delay

    // safe_mutex(philo.t_write_mtx, LOCK);
    // printf(CYAN "philo [%d] joins dinners\n" RESET, (int)philo.philo_id);
    // // printf(WHITE "delay.tv = %ld\n" RESET, (long)get_time(&delay,GET,MILISECONDS));
    // printf(BLUE "ndelaying = %ld\n" RESET, delay_to_sync);
    // printf(YELLOW "nthreshold = %ld\n" RESET, philo.threshold);
    // printf(YELLOW "nthreshold = %ld\n" RESET, (long)philo.settings->threshold);

    safe_mutex(philo.t_write_mtx, UNLOCK);

    if (philo.philo_id % 2 == 0)
    {
        routine_even(&philo);
    }
    else
    {
        routine_odd(&philo);
    }

    safe_mutex(philo.t_write_mtx, LOCK);

    printf(PINK "philo [%d] LEAVING DINNER IN MAIN THREAD\n" RESET, (int)philo.philo_id);
    printf(WHITE "philo [%d] \n return status = %d\n" RESET, (int)philo.philo_id, (int)*philo.return_status[philo.philo_id - 1]);
    safe_mutex(philo.t_write_mtx, UNLOCK);

    return ret;
}

/**
 * @brief evaluates return_status, then it procceds with action, or quits
 *
 * @param philo
 */
int routine_even(t_philo *philo)
{
    int ret;
    int ret2;
    int ret3;

    // safe_mutex(philo->t_write_mtx, LOCK);
    // printf(YELLOW "[%ld] %ld in EVEN\n" RESET, philo->philo_id, get_time(NULL, GET, MILISECONDS));
    // safe_mutex(philo->t_write_mtx, UNLOCK);

    while (1)
    { // previous mutex status for all of them.  philo->settings->status_mtx;
        ret = eating(philo);
        ret2 = sleeping(philo);
        ret3 = thinking(philo);
        // safe_mutex(philo->t_write_mtx, LOCK);
        // printf(WHITE "[%ld] RET = %d\n" RESET, philo->philo_id, ret);
        // safe_mutex(philo->t_write_mtx, UNLOCK);

        if (ret != 0)
            return ret;
        if (ret != 0)
            return ret2;
        if (ret != 0)
            return ret3;
        // write(1,"evv\n", 2);
    }

    (void)philo;
}

int routine_odd(t_philo *philo)
{
    int ret;
    int ret2;
    int ret3;

    // safe_mutex(philo->t_write_mtx, LOCK);
    // printf(YELLOW "[%ld] %ld in ODD\n" RESET, philo->philo_id, get_time(NULL, GET, MILISECONDS));
    // safe_mutex(philo->t_write_mtx, UNLOCK);

    while (1)
    { // previous mutex status for all of them.  philo->settings->status_mtx;
        ret2 = sleeping(philo);
        ret3 = thinking(philo);
        ret = eating(philo);

        // safe_mutex(philo->t_write_mtx, LOCK);
        // printf(WHITE "[%ld] RET = %d\n" RESET, philo->philo_id, ret);
        // safe_mutex(philo->t_write_mtx, UNLOCK);

        if (ret != 0)
            return ret2;
        if (ret != 0)
            return ret3;
        if (ret != 0)
            return ret;
        // write(1,"evv\n", 2);
    }

    (void)philo;
}

// void check_deaths(t_settings *settings)
// {
//     int i;
//     safe_mutex(settings->t_write_mtx, LOCK);

//     printf(RED "Got into checking deaths\n\n" RESET);
//     safe_mutex(settings->t_write_mtx, UNLOCK);

//     while (ALL_ALIVE)
//     {
//         safe_mutex(settings->t_write_mtx, LOCK);

//         printf(RED "Got into checking deaths\n\n" RESET);
//         safe_mutex(settings->t_write_mtx, UNLOCK);

//         i = 0;
//         safe_mutex(settings->t_common_status_mtx, LOCK);
//         while (settings->num_philosophers > i)
//         {
//             if (settings->philo_status[i] == ONE_DIED)
//                 settings->funeral = ONE_DIED;
//             if (settings->philo_status[i] == FULL)
//                 settings->all_full--;
//             i++;
//         }
//         safe_mutex(settings->t_common_status_mtx, UNLOCK);
//         usleep(100000);
//     }
// }
