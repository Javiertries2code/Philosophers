void create_mutexes(t_settings *settings)
{
    int i;

    i = 0;
    settings->t_write_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->t_common_status_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->t_maitre_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    settings->time_mtx = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
    ////////////
    //WEIRD AS FUCK 
    /*
    IT DOESNT SEEM TO CREATE NUM-PHILOSOFER GAPS FOR THE MUTEXES, recurrent probelm of allowing
    only 4 out of 5 philos, when blocking status in eating, the fail is experienced in staus mtx, but in case
    of i added the +1 in all mallocs*/
    /////
    settings->mutexes = (pthread_mutex_t *)ft_calloc(settings->num_philosophers +1, sizeof(pthread_mutex_t));
    settings->status_mtx = (pthread_mutex_t *)ft_calloc(settings->num_philosophers +1, sizeof(pthread_mutex_t ));
    settings->meal_mtx = (pthread_mutex_t *)ft_calloc(settings->num_philosophers +1, sizeof(pthread_mutex_t));
