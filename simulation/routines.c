#include "../philo.h"
/**
 * @brief
 *
 * @param philo
 * @return int
 */
int take_nap(t_philo *philo)
{
    long int time_to_sleep;
    ;

    safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
    if (philo->settings->return_status[philo->philo_id - 1][0] == ONE_DIED)
        return (ONE_DIED);
    safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);
    time_to_sleep = time_left(philo);
    if (time_to_sleep < philo->time_to_sleep && time_to_sleep > 0)
    {
    precise_sleep((time_to_sleep - 1), &philo->threshold);
    safe_mutex(philo->t_write_mtx, LOCK);
    printf(YELLOW "% ld %ld died\n" RESET, get_time(NULL, GET, MILISECONDS), philo->philo_id);
    safe_mutex(philo->t_write_mtx, UNLOCK);
    return (ONE_DIED);
    }

    else if (time_to_sleep <= 0)
        return (ONE_DIED);
return (0);
}
/**
 * @brief
 *
 * @param philo
 * @return long int
 */
long int time_left(t_philo *philo)
{
    long int time_left;
    long int last_meal;
    safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
    last_meal = philo->last_meal;
    safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);
    time_left = philo->time_to_eat -(get_time(NULL, GET, MILISECONDS) - last_meal);
    return (time_left);
}