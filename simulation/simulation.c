#include "../philo.h"
/*
The idea is that it cheacks the start simulation, for a inchronuous starting, same as
all alive, to quite, hence the data it should
*/
void *routine_ph(void *args)
{
    t_philo philo;
    
    struct timeval delay;
    struct timeval current_time;
    struct timeval elapsed_time;
    

    
sleep(2);
    philo = *(t_philo *)args;
   printf(CYAN "philo [%d] joins dinners\n" RESET, (int)philo.philo_id);
    // //delay to avoid concurrrency when accessing the start time
    usleep(10000);
    //calculates the dalay when waking up, and makes them wait just enough to wake up the same time.
    gettimeofday(&current_time,NULL);
    if((int)philo.philo_id == 1)
         printf("current = %ld\nstart = %ld", (long) current_time.tv_usec, philo.settings->starting_time.tv_usec);
    delay.tv_usec = 1000000;
    elapsed_time.tv_usec = current_time.tv_usec - philo.settings->starting_time.tv_usec;
   if (elapsed_time.tv_usec > 1000000)
        printf("ERROR");
    else
     usleep(delay.tv_usec -(elapsed_time.tv_usec));

    //while (!philo.settings->start_simulation);
    
    //printf("philo.settings->start_simulation == %d\n", (int)philo.settings->start_simulation);

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
//para sanitizer
break;
    }
    exit(0);
    return NULL;
}