#include "../philo.h"

void join_threads(t_settings *settings)
{
    int i;

    i = -1;
  
        
        while (settings->num_ph > ++i)
        {
            void *ret;
            pthread_join(settings->philos[i].thread_id, &ret);
            if (*(int *)ret == FULL)
            {
            safe_mutex(settings->feed_mtx, LOCK);
           settings->all_full--;
            safe_mutex(settings->feed_mtx, UNLOCK);
            }
        }
    	if (settings->asist)
		pthread_join(settings->asist->th_asist, NULL);
	if (settings->nd_asist)
		pthread_join(settings->nd_asist->th_asist, NULL);
	if (settings->third_asist)
		pthread_join(settings->third_asist->th_asist, NULL);
	if (settings->fourth_asist)
		pthread_join(settings->fourth_asist->th_asist, NULL);
	if (settings->fifth_asist)
		pthread_join(settings->fifth_asist->th_asist, NULL);
	if (settings->sixth_asist)
		pthread_join(settings->sixth_asist->th_asist, NULL);
}