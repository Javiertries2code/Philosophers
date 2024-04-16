#include "../philo.h"


int eating(t_philo *philo)
{
int var_status;
// safe_mutex(philo->t_write_mtx, LOCK);
// printf(YELLOW "[%ld] in eating\n" RESET, philo->philo_id);
// safe_mutex(philo->t_write_mtx, UNLOCK);

safe_mutex(philo->t_write_mtx, LOCK);
printf(BLUE "[%ld] max meal[%ld] \n" RESET,philo->philo_id, philo->max_meals);
safe_mutex(philo->t_write_mtx, UNLOCK);

if (philo->max_meals == 0)
 { 
safe_mutex(philo->t_write_mtx, LOCK);
printf(YELLOW "[%ld] is FULL\n" RESET, philo->philo_id);
safe_mutex(philo->t_write_mtx, UNLOCK);

safe_mutex(philo->status_mtx, LOCK);
philo->return_status[philo->philo_id -1][0] = FULL;
safe_mutex(philo->status_mtx, UNLOCK);
return (FULL);
}
//locking both and checking status;
safe_mutex(philo->t_write_mtx, LOCK);
safe_mutex(philo->status_mtx, LOCK);

var_status = philo->return_status[philo->philo_id -1][0];
if(var_status != 0)
    return var_status;

safe_mutex(philo->first_fork, LOCK);
printf(RED "% ld %ld has taken a fork\n" RESET, get_time(NULL, GET, MILISECONDS), (long)philo->philo_id);

safe_mutex(philo->second_fork, LOCK);
printf(RED "% ld %ld has taken a fork\n" RESET, get_time(NULL, GET, MILISECONDS), (long)philo->philo_id);

// safe_mutex(philo->settings->philosophers[philo->philo_id -1].fork_next, LOCK);
// safe_mutex(philo->settings->philosophers[philo->philo_id -1].fork_prev, LOCK);

printf(RED "% ld %ld is eating\n" RESET, get_time(NULL, GET, MILISECONDS), (long)philo->philo_id);
//as in time left is using also philo statusmtx[i], same a mtx, it should work by now, 
//actually better than doing a meal[];
philo->last_meal = get_time(NULL, GET,MILISECONDS);

// safe_mutex(philo->settings->philosophers[philo->philo_id -1].fork_prev, UNLOCK);
// safe_mutex(philo->settings->philosophers[philo->philo_id -1].fork_next, UNLOCK);

safe_mutex(philo->first_fork, UNLOCK);
safe_mutex(philo->second_fork, UNLOCK);

safe_mutex(philo->status_mtx, UNLOCK);
safe_mutex(philo->t_write_mtx, UNLOCK);
precise_sleep(philo->time_to_sleep, &philo->threshold);
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
    //here i should use a meal[] mutex; though i am using the stats in eatin
    safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], LOCK);
    last_meal = philo->last_meal;
    safe_mutex(&philo->settings->status_mtx[philo->philo_id - 1], UNLOCK);
    time_left = philo->time_to_eat -(get_time(NULL, GET, MILISECONDS) - last_meal);
    return (time_left);
}