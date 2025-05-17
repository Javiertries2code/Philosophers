#include "../philo.h"
int eating(t_philo *philo)
{
    int var_status;

    safe_mutex(philo->first_fork, LOCK);
    var_status = all_alive(philo, FORK);
    if (var_status != ALL_ALIVE) {
        safe_mutex(philo->first_fork, UNLOCK);
        return var_status;
    }
    //TEST, this should do well enough in case of one only filo
    if(philo->settings->num_philosophers == 1)
    {
        safe_mutex(philo->first_fork, UNLOCK);
        return ONE_DIED;    
    }

    safe_mutex(philo->second_fork, LOCK);

       //has dinner just when entering
        safe_mutex(philo->meal_mtx, LOCK);
        philo->last_meal = get_time(NULL, GET, MILISECONDS);
        safe_mutex(philo->meal_mtx, UNLOCK);

    var_status = all_alive(philo, FORK2);
    if (var_status != ALL_ALIVE) {
        safe_mutex(philo->second_fork, UNLOCK);
        safe_mutex(philo->first_fork, UNLOCK);
        return var_status;
    }

 

    precise_sleep(philo->time_to_eat, &philo->threshold);
    safe_mutex(philo->meal_mtx, LOCK);

    philo->max_meals--;
    safe_mutex(philo->meal_mtx, UNLOCK);

    if (philo->max_meals == 0)
    {
        //TEST FULL
        // safe_mutex(philo->t_write_mtx, LOCK);
        // printf(YELLOW "%ld  [%ld] is FULL in eating\n" RESET,
        //        (get_time(NULL, GET, MILISECONDS) - philo->settings->starting_time),
        //        philo->philo_id);
        // safe_mutex(philo->t_write_mtx, UNLOCK);

        safe_mutex(philo->status_mtx, LOCK);
        *philo->return_status= FULL;
        safe_mutex(philo->status_mtx, UNLOCK);

        safe_mutex(philo->first_fork, UNLOCK);
        safe_mutex(philo->second_fork, UNLOCK);
        return FULL;
    }

    safe_mutex(philo->first_fork, UNLOCK);
    safe_mutex(philo->second_fork, UNLOCK);
    return var_status;
}


long int time_left(t_philo *philo)
{
    long int time_left;
    long int last_meal;
    //    safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
    safe_mutex(philo->meal_mtx, LOCK);
    last_meal = philo->last_meal;
    safe_mutex(philo->meal_mtx, UNLOCK);
    // safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);
    time_left = philo->time_to_die - (get_time(NULL, GET, MILISECONDS) - last_meal);


    return (time_left);
}

int thinking(t_philo *philo)
{

    int var_status;
    var_status = all_alive(philo, THINKING);

    return (var_status);
}

int sleeping(t_philo *philo)
{
    // support_read_returns(philo->settings);

    int var_status;

  

    var_status = all_alive(philo, SLEEPING);

    precise_sleep(philo->time_to_sleep, &philo->threshold);
    return var_status;
}
