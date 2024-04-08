#include "../philo.h"
#include "stdlib.h"
void ft_bzero(void *s, size_t n)
{
	unsigned int i;
	char *str;

	str = (char *)s;
	i = 0;
	while (i < n)
		str[i++] = '\0';
}

void *ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/**
 * @brief Counts the lenght of an String, number of characters, excluded
 *  the closing chracter. "HOLA" returns 4
 *
 * @param s
 * @return size_t  the number of caracters
 */

size_t ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void *print(char *str)
{
}

/**
 * @brief it calculates the time all philos must delay for a sinchronised begining
 * under the thresold of 1000 ml fro 
 * @param delay 
 * @param synchro_t 
 * @param write_mtx 
 */
void calculate_delay(struct timeval *delay, struct timeval synchro_t, write_mtx write_mtx)
{
    struct timeval current_time;
    struct timeval elapsed_time;
    struct timeval begining;
    
		delay->tv_usec = SAND_CLOCK;//pending to remove elpased time

    // calculates the dalay when waking up, and makes them wait just enough to wake up the same time.
    begining.tv_usec = synchro_t.tv_usec;    
   // pthread_mutex_lock(philo.t_time_mtx);
    gettimeofday(&current_time, NULL);
   // pthread_mutex_unlock(philo.t_time_mtx);

   //elapsed time
    elapsed_time.tv_usec = current_time.tv_usec - begining.tv_usec;
   
    if (elapsed_time.tv_usec > SAND_CLOCK)
        printf("ERROR");
    else
        delay->tv_usec -= elapsed_time.tv_usec;

     pthread_mutex_lock(write_mtx);

	printf("current time = %ld\nbegining = %ld\nelapsed = %ld, planned delay = %ld\n",
	 (long)current_time.tv_usec , (long)begining.tv_usec, (long)elapsed_time.tv_usec, (long)delay->tv_usec);
    pthread_mutex_unlock(write_mtx);

}
