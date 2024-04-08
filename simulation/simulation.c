#include "../philo.h"
/*
The idea is that it cheacks the start simulation, for a inchronuous starting, same as
all alive, to quite, hence the data it should
*/
void *routine_ph(void *args)
{
    t_philo philo;

    struct timeval delay;
    // struct timeval current_time;
    // struct timeval elapsed_time;
    // struct timeval time_of_start;

    sleep(1);
    philo = *(t_philo *)args;
    printf(CYAN "philo [%d] joins dinners\n" RESET, (int)philo.philo_id);
    // //delay to avoid concurrrency when accessing the start time
    usleep(10000);
 calculate_delay(&delay, philo.settings->synchro_t, philo.write_mtx);

     pthread_mutex_lock(philo.write_mtx);

	printf(GREEN"DELAYED= %ld\n"RESET,(long)delay.tv_usec);
    pthread_mutex_unlock(philo.write_mtx);

    while (philo.settings->all_alive)
    {
        if (philo.philo_id % 2 == 0)
        {
            pthread_mutex_lock(philo.write_mtx);
            printf(CYAN "philo [%d] is EVEN \n" RESET, (int)philo.philo_id);

            pthread_mutex_unlock(philo.write_mtx);
        }
        else
        {
            pthread_mutex_lock(philo.write_mtx);
            printf(YELLOW "philo [%d]  is ODD\n" RESET, (int)philo.philo_id);

            pthread_mutex_unlock(philo.write_mtx);
        }
        usleep(500000);
        // para sanitizer
        break;
    }
    exit(0);
    return NULL;
}