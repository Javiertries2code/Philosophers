#include "../philo.h"
/*
The idea is that it cheacks the start simulation, for a inchronuous starting, same as
all alive, to quite, hence the data it should
*/
void *routine_ph(void *args)
{
    t_philo philo;
    struct timeval delay;
    philo = *(t_philo *)args;
    //I cant use a mutex before, as the phile is created before
   printf("*(t_philo *)args).thread_id = %ld\n ", (*(t_philo *)args).thread_id);
   // pthread_mutex_lock((*(t_philo *)args).t_general);
 
    //pthread_mutex_unlock(philo.t_general);

    printf(CYAN"philo [%d] joins dinners\n"RESET, (int)philo.philo_id);
    // //delay to avoid concurrrency when accessing the start time

   usleep(1000);

    //lock philo to access get timeof day
    pthread_mutex_lock(philo.time_mtx);
    write(1,"MUTEX to calculate delay\n",18 );

    calculate_delay(&delay, philo.settings->synchro_t, philo.write_mtx);
    printf(GREEN"[%ld] --- DELAYED= %ld\n"RESET, philo.philo_id,(long)delay.tv_usec);

    pthread_mutex_unlock(philo.time_mtx);
    sleep(2);
// if((philo.philo_id %2 )!= 0)
//     routine_even(&philo);
// else
//     routine_odd(&philo);
    
     //pthread_mutex_lock(philo.write_mtx);

   // pthread_mutex_unlock(philo.write_mtx);


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
    sleep(2);
    exit(0);
    return NULL;
}

void *routine_maitre(void *args)
{
   (void)args;
write(1,"HERE IS THE MAITRE\n",20);
return NULL;
}

 void routine_even( t_philo *philo)
{
   (void)philo;
}

 void routine_odd( t_philo *philo)
{
(void)philo;
}

    void write_function( write_mtx write_mtx){
        (void)write_mtx;
    }
    
