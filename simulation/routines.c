#include "../philo.h"

int eating(t_philo *philo)
{
    // support_read_returns(philo->settings);

    int var_status;

    if (philo->max_meals == 0)
    {

        safe_mutex(philo->t_write_mtx, LOCK);
        printf(YELLOW "[%ld] is FULL\n" RESET, philo->philo_id);
        safe_mutex(philo->t_write_mtx, UNLOCK);

        safe_mutex(&philo->status_mtx[philo->philo_id], LOCK);
        philo->return_status[philo->philo_id - 1][0] = FULL;
        safe_mutex(&philo->status_mtx[philo->philo_id], UNLOCK);
        return (FULL);
    }
    safe_mutex(&philo->status_mtx[philo->philo_id], LOCK);
    var_status = philo->return_status[philo->philo_id - 1][0];

    if (var_status != 0)
  {  safe_mutex(&philo->status_mtx[philo->philo_id], UNLOCK);
        return var_status;}

    
    safe_mutex(philo->first_fork, LOCK);
    safe_mutex(philo->t_write_mtx, LOCK);

    printf(RED "% ld %ld has taken a fork\n" RESET, get_time(NULL, GET, MILISECONDS), (long)philo->philo_id);
    safe_mutex(philo->t_write_mtx, UNLOCK);

    safe_mutex(philo->second_fork, LOCK);
    safe_mutex(philo->t_write_mtx, LOCK);
    printf(RED "% ld %ld has taken a fork\n" RESET, get_time(NULL, GET, MILISECONDS), (long)philo->philo_id);

    printf(RED "% ld %ld is eating\n" RESET, get_time(NULL, GET, MILISECONDS), (long)philo->philo_id);
    safe_mutex(philo->t_write_mtx, UNLOCK);
    philo->last_meal = get_time(NULL, GET, MILISECONDS);

    safe_mutex(philo->first_fork, UNLOCK);
    safe_mutex(philo->second_fork, UNLOCK);
    safe_mutex(&philo->status_mtx[philo->philo_id], UNLOCK);


    safe_mutex(philo->t_write_mtx, UNLOCK);
    precise_sleep(philo->time_to_eat, &philo->threshold);
    philo->max_meals--;
    return ALL_ALIVE;
}

/**
 * @brief
 *
 * @param philo
 * @return int
 */
int take_nap(t_philo *philo)
{
    long int time_to_sleep;

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
    safe_mutex(&philo->status_mtx[philo->philo_id -1], LOCK);
    last_meal = philo->last_meal;
    safe_mutex(&philo->status_mtx[philo->philo_id -1], UNLOCK);
   // safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);
    time_left = philo->time_to_die - (get_time(NULL, GET, MILISECONDS) - last_meal);
    return (time_left);
}

int thinking(t_philo *philo)
{
    // support_read_returns(philo->settings);

    int var_status;

    safe_mutex(&philo->status_mtx[philo->philo_id], LOCK);
    var_status = philo->return_status[philo->philo_id - 1][0];

    if (var_status != 0)
    {
        safe_mutex(&philo->status_mtx[philo->philo_id], UNLOCK);
        return var_status;
    }
    else
    {
        safe_mutex(philo->t_write_mtx, LOCK);

        printf(RED "% ld %ld is thinking\n" RESET, get_time(NULL, GET, MILISECONDS), (long)philo->philo_id);
        safe_mutex(philo->t_write_mtx, UNLOCK);
        safe_mutex(&philo->status_mtx[philo->philo_id], UNLOCK);
    }

    return (ALL_ALIVE);
}

int sleeping(t_philo *philo)
{
    // support_read_returns(philo->settings);

    int var_status;

    safe_mutex(&philo->status_mtx[philo->philo_id], LOCK);
    var_status = philo->return_status[philo->philo_id - 1][0];

    if (var_status != 0)
    {
        safe_mutex(&philo->status_mtx[philo->philo_id], UNLOCK);
        return var_status;
    }
    else
    {
        safe_mutex(philo->t_write_mtx, LOCK);

        printf(RED "% ld %ld is sleeping\n" RESET, get_time(NULL, GET, MILISECONDS), (long)philo->philo_id);
        safe_mutex(philo->t_write_mtx, UNLOCK);
        safe_mutex(&philo->status_mtx[philo->philo_id], UNLOCK);
    }

    precise_sleep(philo->time_to_sleep, &philo->threshold);
    return ALL_ALIVE;
}
