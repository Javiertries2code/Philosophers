#include "../philo.h"

long delay_to_syncro(long *delay, long* synchro_t, t_write_mtx t_write_mtx)
{
    long current_time;
    long elapsed_time;
    long begining;
   
 safe_mutex(t_write_mtx, LOCK);
        safe_mutex(t_write_mtx, UNLOCK);
    *delay = (long)SAND_CLOCK;
    begining = *synchro_t;
    current_time = get_time(NULL, GET, MILISECONDS);
    elapsed_time = current_time - begining;
        // safe_mutex(t_write_mtx, LOCK);
        // printf("delay = %ld\n", *delay );
        // printf("begining = %ld\n", begining);
        // printf("current_time = %ld\n", current_time );
        // printf("elapsed_time  = %ld\n", elapsed_time  );
        // safe_mutex(t_write_mtx, UNLOCK);
    if (elapsed_time > SAND_CLOCK)
    {
        safe_mutex(t_write_mtx, LOCK);
        printf("ERROR: Elapsed time > SAND_CLOCK\nUncontrolled for resetting purposses");
        safe_mutex(t_write_mtx, UNLOCK);
        return(EXIT_FAILURE);
    }
    else
       return (*delay - elapsed_time);
    // this would reasult in adding repetitevely, and a data race   
   //*synchro_t += SAND_CLOCK;
}

/**
 * @brief it handles conversion of units, or adquiring current time, depending on the args
 *
 *
 * @param tv
 * @param operation either  return in provided units, or adquiring current time
 * @param units  type of unit of the return provided
 * @return long  time in units provided
 */
long get_time(timeval *tv, timing_options operation, timing_options units)
{
    if (operation == GET)
    {
        if (units == MILISECONDS)
            return (get_milisec());
        if (units == MICROSECONDS)
            return (get_microsec());
    }
    else if (operation == CHANGE)
    {
        if (units == MILISECONDS)
            return ((long)tv->tv_sec * 1e3 + tv->tv_usec / 1e3);
        if (units == MICROSECONDS)
            return ((long)tv->tv_sec * 1e6 + tv->tv_usec);
    }
    exit_on_error("Error calling get_time()\n");
    return (EXIT_FAILURE);
}

long to_microsec(timeval *tv)
{
    return ((long)tv->tv_sec * 1e6 + tv->tv_usec);
}

long to_milisec(timeval *tv)
{
    return ((long)tv->tv_sec * 1e3 + tv->tv_usec / 1e3);
}

long get_microsec()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return ((long)tv.tv_sec * 1e6 + tv.tv_usec);
}

long get_milisec()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return ((long)tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}
