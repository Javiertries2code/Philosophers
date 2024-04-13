#include "../philo.h"

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
            return (get_mili_sec());
        if (units == MICROSECONDS)
            return (get_microsec());
    }
    else if(operation == CHANGE)
        {
            if (units == MILISECONDS)
                return ((long)tv->tv_sec * 1e3 + tv->tv_usec / 1e3);
            if (units == MICROSECONDS)
                return ((long)tv->tv_sec * 1e6 + tv->tv_usec);
        }
    exit_on_error("Error calling get_time()");
    return (EXIT_FAILURE);
}

long	to_microsec(timeval *tv)
{
	return ((long)tv->tv_sec * 1e6 + tv->tv_usec);
}

long	to_milisec(timeval *tv)
{
	return ((long)tv->tv_sec * 1e3 + tv->tv_usec / 1e3);
}

long	get_microsec()
{
	timeval	tv;
	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1e6 + tv.tv_usec);
}

long	get_mili_sec()
{
	timeval	tv;
	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}
