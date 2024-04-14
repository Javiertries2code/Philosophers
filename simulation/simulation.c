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
void *routine_maitre(void *args)
{
    t_maitre maitre;
    long int i;
    long int time_left_die;

    maitre = *(t_maitre *)args;
    // safe_mutex(maitre.write_mtx, LOCK);
    // printf(YELLOW "In MAITRE 2 --- num philos %ld \n" RESET, maitre.num_philosophers);
    // safe_mutex(maitre.write_mtx, UNLOCK);
    //////
    // int *ret;
    /////
    while (true)
    {
        i = 0;
        while (maitre.num_philosophers > i)
        {
            safe_mutex(maitre.meal_mtx, LOCK);
            time_left_die = time_left(&(maitre.philosophers[i]));
            ////////////////////
            // ret = &maitre.return_status[i][0];
            // printf(YELLOW "philo[%ld] status = %d \n" RESET, (i + 1), *ret);
            // safe_mutex(maitre.write_mtx, LOCK);
            // printf(YELLOW "In MAITRE philo[%ld] time_left_die = %ld \n" RESET, i + 1, time_left_die);
            // printf(YELLOW "philo[%ld] LAst meal  = %ld \n" RESET, i + 1, maitre.philosophers[i].last_meal);

            // safe_mutex(maitre.write_mtx, UNLOCK);
            ///////////////////////////

            safe_mutex(maitre.meal_mtx, UNLOCK);
            if (time_left_die <= 0)
            {//NECESARIA, IMPRIME MUERTOS
                safe_mutex(maitre.write_mtx, LOCK);
                printf(YELLOW "% ld %ld died\n" RESET, get_time(NULL, GET, MILISECONDS), (long)maitre.philosophers[i].philo_id);
                safe_mutex(maitre.write_mtx, UNLOCK);
                i = 0;
                while (maitre.num_philosophers > i)
                {
                    safe_mutex(maitre.status_mtx, LOCK);
                    maitre.return_status[i][0] = ONE_DIED;
                    safe_mutex(maitre.status_mtx, UNLOCK);
                    // safe_mutex(maitre.write_mtx, LOCK);
                    // printf(YELLOW "philo[%ld] maitre.return_status[i][0]= %d \n" RESET, (i + 1), maitre.return_status[i][0]);
                    // safe_mutex(maitre.write_mtx, UNLOCK);
                    i++;
                }
                return (NULL);
            }
            i++;
        }
    }
    return (NULL);
}
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
    safe_mutex(philo.t_write_mtx, LOCK);
    printf(RED "[delay_to_sync =  %ld\n philo.threshold = %ld\n" RESET, delay_to_sync, philo.threshold);
    safe_mutex(philo.t_write_mtx, UNLOCK);
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
    safe_mutex(philo->t_write_mtx, LOCK);
    printf(PINK "[%ld] %ld in EVEN\n" RESET, philo->philo_id, get_time(NULL, GET, MILISECONDS));
    safe_mutex(philo->t_write_mtx, UNLOCK);
    return 0; ////////////

    while (true)
    { // previous mutex status for all of them.  philo->settings->status_mtx;
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if (philo->settings->return_status[philo->philo_id - 1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        // think();
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if (philo->settings->return_status[philo->philo_id - 1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        // eat();
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if (philo->settings->return_status[philo->philo_id - 1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        // take_nap(); this could simply be a preccise sleep(sleeping time);
    }

    // pthread_mutex_lock(philo->t_write_mtx);
    safe_mutex(philo->t_write_mtx, LOCK);
    printf(YELLOW "philo [%d]  is EVEN\n" RESET, (int)philo->philo_id);
    safe_mutex(philo->t_write_mtx, UNLOCK);
    sleep(1);
    // pthread_mutex_unlock(philo->t_write_mtx);

    (void)philo;
}

int routine_odd(t_philo *philo)
{
    safe_mutex(philo->t_write_mtx, LOCK);
    printf(YELLOW "[%ld] %ld  In OOD\n" RESET, philo->philo_id, get_time(NULL, GET, MILISECONDS));
    safe_mutex(philo->t_write_mtx, UNLOCK);

    while (true)
    { // previous mutex status for all of them.  philo->settings->status_mtx;

        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if (philo->settings->return_status[philo->philo_id - 1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        // think();
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if (philo->settings->return_status[philo->philo_id - 1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        // eat();
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
        if (philo->settings->return_status[philo->philo_id - 1][0] == ONE_DIED)
            return (ONE_DIED);
        safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);

        // take_nap(); this could simply be a preccise sleep(sleeping time);
    }
    // pthread_mutex_lock(philo->t_write_mtx);
    safe_mutex(philo->t_write_mtx, LOCK);

    printf(RED "philo [%d]  is ODD\n" RESET, (int)philo->philo_id);
    safe_mutex(philo->t_write_mtx, UNLOCK);
    sleep(1);

    // pthread_mutex_unlock(philo->t_write_mtx);
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
