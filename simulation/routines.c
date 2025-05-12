#include "../philo.h"
/**
 * @brief 
 * 1 -First it evaluates if the maximun number of meals went down to 0, if so, it sets status 
 * to FULL and quits. max-meal is in the struct, no need of mutex
 * 2- LOCKS status check 
 * (it has individual mutex for every philo), (if != 0 ) means anyone died
 * UNLOCKS and quits
 * 3- Else.  previous LOCK remains
 * it tries to get a mutex fork, prints, gets second mutex fork, prints, UNLOCK forks
 * mutex meal_mtx[philo->philo_id - 1], updates last meal-time, UNLOCKS status, SLEEPS, max meal --;
 *
 *
 * @param philo
 * @return int
 */
int eating(t_philo *philo)
{
    int var_status;

    safe_mutex(philo->first_fork, LOCK);
    var_status = all_alive(philo, FORK);
    if (var_status != ALL_ALIVE) {
        safe_mutex(philo->first_fork, UNLOCK);
        return var_status;
    }

    safe_mutex(philo->second_fork, LOCK);
    var_status = all_alive(philo, FORK2);
    if (var_status != ALL_ALIVE) {
        safe_mutex(philo->second_fork, UNLOCK);
        safe_mutex(philo->first_fork, UNLOCK);
        return var_status;
    }

    // Ya con ambos forks bloqueados
    safe_mutex(&philo->meal_mtx[philo->philo_id - 1], LOCK);
    philo->last_meal = get_time(NULL, GET, MILISECONDS);
    safe_mutex(&philo->meal_mtx[philo->philo_id - 1], UNLOCK);

    precise_sleep(philo->time_to_eat, &philo->threshold);

    philo->max_meals--;
    if (philo->max_meals == 0)
    {
        safe_mutex(philo->t_write_mtx, LOCK);
        printf(YELLOW "%ld  [%ld] is FULL\n" RESET,
               (get_time(NULL, GET, MILISECONDS) - philo->settings->starting_time),
               philo->philo_id);
        safe_mutex(philo->t_write_mtx, UNLOCK);

        safe_mutex(&philo->status_mtx[philo->philo_id - 1], LOCK);
        philo->return_status[philo->philo_id - 1][0] = FULL;
        safe_mutex(&philo->status_mtx[philo->philo_id - 1], UNLOCK);

        safe_mutex(philo->first_fork, UNLOCK);
        safe_mutex(philo->second_fork, UNLOCK);
        return FULL;
    }

    safe_mutex(philo->first_fork, UNLOCK);
    safe_mutex(philo->second_fork, UNLOCK);
    return var_status;
}


/**
 * @brief calculates the diferrence betwen the time elapsed since the last meal.
 *
 * @param philo
 * @return long int
 */
long int time_left(t_philo *philo)
{
    long int time_left;
    long int last_meal;
    //    safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
    safe_mutex(&philo->meal_mtx[philo->philo_id - 1], LOCK);
    last_meal = philo->last_meal;
    safe_mutex(&philo->meal_mtx[philo->philo_id - 1], UNLOCK);
    // safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);
    time_left = philo->time_to_die - (get_time(NULL, GET, MILISECONDS) - last_meal);
//test
    // safe_mutex(philo->t_write_mtx, LOCK);
    // printf(YELLOW " in time_left%ld  [%ld] TIME LEFT TO DIE\n" RESET, time_left, philo->philo_id);
    // safe_mutex(philo->t_write_mtx, UNLOCK);

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
