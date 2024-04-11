#include "../philo.h"

void set_threshold(t_settings *settings)
{
    
    long current;
    long start;

    long max_sleep;

    settings->max_thr= 0;
    settings->threshold = 0;
    if (settings->time_to_eat >= settings->time_to_die)
        max_sleep = settings->time_to_eat;
    else
        max_sleep = settings->time_to_die;
    
   for (int i = 0; i < THRESHOLD_TEST_ITERATION; i++)
    {
        start = get_microsec();
        usleep(max_sleep);
        current = get_microsec();

        settings->max_thr = current - start - (long)max_sleep;
        if (settings->max_thr > settings->threshold)
            settings->threshold = settings->max_thr;
    }
        printf(YELLOW " YYset_threshold: threshold max with sleeping time %ld\n;  new sleeping threshold = %ld\n" RESET, (long)max_sleep, settings->threshold);

funcion_proporcional(settings);
        printf(BLUE"   new  threshold = %ld\n" RESET,  settings->threshold);

}
void funcion_proporcional(t_settings *settings) {
    // Definir los límites de la función

    float input_min = 150;
    float input_max = settings->max_thr;
    float output_min = MIN_SAFETY_MARGIN;
    float output_max = MAX_SAFETY_MARGIN;
    float input = (float)settings->threshold;
    float output;
    
    if (input < input_min)
        input = input_min;
    else if (input > input_max)
        input = input_max;
     output = ((input - input_min) / (input_max - input_min)) * (output_max - output_min) + output_min;
      
    settings->threshold *= output;   
}

long to_microsec(timeval *tv)
{
    return ((long)tv->tv_sec * 1e6 + tv->tv_usec);
}

long get_microsec()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return ((long)tv.tv_sec * 1e6 + tv.tv_usec);
}

void precise_sleep(long nap_time, long *threshold)
{
long start;

start = get_microsec();
usleep(nap_time - *threshold);

while (get_microsec()- start < nap_time)
	;
//printf("diff precise = %ld\n", get_microsec()- start );
}


/**
 * @brief it calculates the time all philos must delay for a sinchronised begining
 * under the threshold of 1000 ml fro 
 * @param delay 
 * @param synchro_t 
 * @param write_mtx 
//  */
void calculate_delay(struct timeval *delay, struct timeval synchro_t, write_mtx write_mtx)
{
    struct timeval current_time;
    struct timeval elapsed_time;
    struct timeval begining;
	//to avoid fail
    (void)write_mtx;
	delay->tv_usec = SAND_CLOCK;
    begining.tv_usec = synchro_t.tv_usec;    
   // pthread_mutex_lock(philo.t_time_mtx);
    gettimeofday(&current_time, NULL);
   // pthread_mutex_unlock(philo.t_time_mtx);
    elapsed_time.tv_usec = current_time.tv_usec - begining.tv_usec;
    if (elapsed_time.tv_usec > SAND_CLOCK)
        printf("ERROR: Elapsed time > SAND_CLOCK");
    else
        delay->tv_usec -= elapsed_time.tv_usec;
	
}