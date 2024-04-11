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
    //I cant use a mutex before, as the phile is created before
    printf("*(t_philo *)args).thread_id = %ld\n ", (*(t_philo *)args).thread_id);
   // pthread_mutex_lock((*(t_philo *)args).t_general);
    philo = *(t_philo *)args;
    //pthread_mutex_unlock(philo.t_general);

    printf(CYAN"philo [%d] joins dinners\n"RESET, (int)philo.philo_id);
    // //delay to avoid concurrrency when accessing the start time
    usleep(10000);
    //lock philo to access get timeof day
    pthread_mutex_lock(philo.time_mtx);
    write(1,"UTILS LOCKS MUTEX\n",18 );

    calculate_delay(&delay, philo.settings->synchro_t, philo.write_mtx);
    printf(GREEN"[%ld] --- DELAYED= %ld\n"RESET, philo.philo_id,(long)delay.tv_usec);

    pthread_mutex_unlock(philo.time_mtx);
    write(1,"UTILS LOCKS MUTEX\n",18 );

     //pthread_mutex_lock(philo.write_mtx);

   // pthread_mutex_unlock(philo.write_mtx);

//data race in here, ofc, as allof themm accesses to check it out

    while (!philo.settings->anyone_death)
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
            printf(PINK "philo [%d]  is ODD\n"RESET, (int)philo.philo_id);

            pthread_mutex_unlock(philo.write_mtx);
        }
        usleep(500000);
        // para sanitizer
        break;
    }
    exit(0);
    return NULL;
}