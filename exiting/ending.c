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
        pthread_join(settings->asist->th_asist, NULL);
        pthread_join(settings->nd_asist->th_asist, NULL);

 
}