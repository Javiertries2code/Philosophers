#include "../philo.h"

/*
The idea is that it cheacks the start simulation, for a inchronuous starting,
	same as
all alive, to quite, hence the data it should

◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

/**
 * @brief it firstlo locks all the return status for each philo,
 * then updates the statu to  ONEDIED
 * unlocks them all
 *
 * @param maitre
 */
void	set_all_died(t_maitre *maitre)
{
	int	i;

	i = 0;
	safe_mutex(maitre->write_mtx, LOCK);
	while (maitre->num_philosophers > i)
	{
		safe_mutex(&maitre->status_mtx[i], LOCK);
		// continously signal data race using
		// valgrind --tool=helgrind-s ./philo^C
		// but it doesnt in real
		maitre->return_status[i][0] = ONE_DIED;
		safe_mutex(&maitre->status_mtx[i], UNLOCK);
		i++;
	}
	safe_mutex(maitre->write_mtx, UNLOCK);
}
/**
 * @brief eternal loop untill it reaturns

	* Locks status[i]  and check if all philos status != FULL (status DEATH is not posible),

	*  as the maitre  would RETURN after anyone dies and overwrite the status to DEATH.
 * it unluck before set_all dead to avoid deathlocks
 *
 * it writes later the "DIED " message when the status was already changed
 * in the routine, it will lock WRITE, adn then lock status,
	so it wouldnt write a new ongoing action
 * if the status was already changed.
 *
 * @param args
 * @return void*
 */

// test
void	*routine_maitre(void *args)
{
	t_maitre	*maitre;
	long int	i;

	maitre = (t_maitre *)args;
	busy_wait_start(maitre->synchro_t, PHILO_HEAD_START);
	safe_mutex(maitre->write_mtx, LOCK);
	 printf(CYAN "Maitre starts =  %ld\n \n" RESET, (get_milisec()-maitre->settings->starting_time));
	safe_mutex(maitre->write_mtx, UNLOCK);
	usleep(300000);
	while (true)
	{
		i = 0;
		while (maitre->num_philosophers > i)
		{
			safe_mutex(&maitre->status_mtx[i], LOCK);
			if (maitre->return_status[i][0] != FULL)
			{ // test
				// safe_mutex(maitre->write_mtx, LOCK);
				// printf(WHITE "\nin maitre id =%ld-- TIME_LEFT%ld  =%ld \n" RESET,
				// 	maitre->philosophers[i].philo_id, i,
				// 	time_left(&(maitre->philosophers[i])));
				// printf(WHITE "maitre last_meal  =%ld \n" RESET,
				// 	(get_milisec() -maitre->philosophers[i].last_meal));
				// safe_mutex(maitre->write_mtx, UNLOCK);
				// test
				// printf("in routine maitre philo_id %ld\n",
				// 	maitre->philosophers[i].philo_id);
				// printf("last_meal %ld\n", maitre->philosophers[i].last_meal);
				// printf("time_left %ld\n", time_left(&(maitre->philosophers[i])));
				if (time_left(&(maitre->philosophers[i])) <= 0)
				{
					maitre->return_status[i][0] = ONE_DIED;
					safe_mutex(&maitre->status_mtx[i], UNLOCK);
					safe_mutex(maitre->write_mtx, LOCK);
					printf(CYAN "%ld %ld died\n" RESET, (get_time(NULL, GET,
								MILISECONDS) - maitre->settings->starting_time),
						(long)maitre->philosophers[i].philo_id);
					safe_mutex(maitre->write_mtx, UNLOCK);
					set_all_died(maitre);
					return (NULL);
				}
				safe_mutex(&maitre->status_mtx[i], UNLOCK);
				i++;
			}
			else // not really possible but as to avoid error valgrind
			{
				safe_mutex(&maitre->status_mtx[i], UNLOCK);
				i++;
			}
		}
	}
}

/**
 * @brief first points to the variable in settings int **return_status;
 * is a array of ints, where the returned variable will be stored,
 * if  death, it will be changed before returning, and after the join happens
 * all member of the array are set to ONEDIED. this is the signal for exiting
 *
 * @param args
 * @return void*
 */
void	*routine_ph(void *args)
{
	t_philo	*philo;
	int		*ret;

	// struct timeval delay;
	// long delay_to_sync;
	philo = (t_philo *)args;
safe_mutex(&philo->status_mtx[philo->philo_id - 1], LOCK);
ret = philo->settings->return_status[philo->philo_id - 1];
safe_mutex(&philo->status_mtx[philo->philo_id - 1], UNLOCK);
	
	busy_wait_start(philo->synchro_t, 0);
    if (philo->settings->starting_time  == 0)
		philo->settings->starting_time = get_time(NULL, GET, MILISECONDS);
	safe_mutex(philo->time_mtx, LOCK);
	philo->last_meal = get_time(NULL, GET, MILISECONDS);
	safe_mutex(philo->time_mtx, UNLOCK);
	safe_mutex(philo->settings->t_write_mtx, LOCK);
	  printf(RED "Philo[%ld] starts simulation=  %ld\n \n" RESET, philo->philo_id, (get_milisec() - philo->settings->starting_time));
		safe_mutex(philo->settings->t_write_mtx, UNLOCK);
		if (philo->philo_id % 2 == 0)
		{
			routine_even(philo);
		}
		else
		{
			routine_odd(philo);
		}
		safe_mutex(philo->t_write_mtx, LOCK);
		 printf(PINK "routine_ph \nphilo [%d] LEAVING DINNER IN MAIN THREAD\n" RESET,(int)philo->philo_id);
		printf(WHITE "philo [%d] \n return (status = %d\n" RESET,(int)philo->philo_id, (int)*philo->return_status[philo->philo_id - 1]);
		 safe_mutex(philo->t_write_mtx, UNLOCK);
		return (ret);
}

/**
 * @brief evaluates return_status, then it procceds with action, or quits
 *
 * @param philo
 */
int	routine_even(t_philo *philo)
{
	int	ret;
	int	ret2;
	int	ret3;


		while (1)
		{
			// previous mutex status for all of them.  philo->settings->status_mtx;
			ret = eating(philo);
			ret2 = sleeping(philo);
			ret3 = thinking(philo);
			// safe_mutex(philo->t_write_mtx, LOCK);
			// printf(WHITE "[%ld] RET = %d\n" RESET, philo->philo_id, ret);
			// safe_mutex(philo->t_write_mtx, UNLOCK);
			if (ret != 0)
				return (ret);
			if (ret2 != 0)
				return (ret2);
			if (ret3 != 0)
				return (ret3);
			// write(1,"evv\n", 2);
		}
		(void)philo;
}

int	routine_odd(t_philo *philo)
{
	int	ret;
	int	ret2;
	int	ret3;

	while (1)
	{
		ret2 = sleeping(philo);
		ret3 = thinking(philo);
		ret = eating(philo);
		if (ret2 != 0)
			return (ret2);
		if (ret3 != 0)
			return (ret3);
		if (ret != 0)
			return (ret);
	}
	(void)philo;
}
void printer(t_write_mtx  t_write_mtx, char *opt, long id, long time)
{
	
char *colors;
//need som comparing from libft
 if ( !strcmp(opt, FORK)|| !strcmp(opt, FORK2))
	colors = BLUE;
 else if (!strcmp(opt, THINKING))
	colors = YELLOW;
 else if (!strcmp(opt, SLEEPING))
	colors = GREEN;
 else if (!strcmp(opt, DIED))
	colors = RED;

safe_mutex(t_write_mtx, LOCK);
if(!strcmp(opt, FORK2)){
		printf("%s%ld %ld has taken a fork%s\n", colors, time, id , RESET);
		printf(PINK"%ld %ld %s%s\n", time, id, EATING , RESET);
}
else
	printf("%s%ld %ld %s%s\n", colors, time, id, opt, RESET);
safe_mutex(t_write_mtx, UNLOCK);
	
}

int all_alive(t_philo *philo,  char *opt ){
    int var_status;
	

if(time_left(philo) <= 0)//Could trick safe using <=1
	{
		safe_mutex(&philo->status_mtx[philo->philo_id - 1], LOCK);
		philo->return_status[philo->philo_id - 1][0] = ONE_DIED;
		safe_mutex(&philo->status_mtx[philo->philo_id -1], UNLOCK);
	
		safe_mutex(philo->t_write_mtx, LOCK);
		printf(YELLOW" in time_left  [%ld] died\n"RESET,  philo->philo_id);
		safe_mutex(philo->t_write_mtx, UNLOCK);
		return ONE_DIED;
	}

	safe_mutex(&philo->status_mtx[philo->philo_id - 1], LOCK);
	
    var_status = philo->return_status[philo->philo_id - 1][0];

if(var_status == ALL_ALIVE){
	printer(philo->t_write_mtx, opt,philo->philo_id, (get_milisec() - philo->settings->starting_time));
}


	safe_mutex(&philo->status_mtx[philo->philo_id -1], UNLOCK);
	return var_status;
    
}

// void check_deaths(t_settings *settings)
// {
//     int i;
//     safe_mutex(settings->t_write_mtx, LOCK);

//     printf(RED "Got into checking deaths\n\n" RESET);
//     safe_mutex(settings->t_write_mtx, UNLOCK);

//     while (ALL_ALIVE)
//     {
//         safe_mutex(settings->t_write_mtx, LOCK);

//         printf(RED "Got into checking deaths\n\n" RESET);
//         safe_mutex(settings->t_write_mtx, UNLOCK);

//         i = 0;
//         safe_mutex(settings->t_common_status_mtx, LOCK);
//         while (settings->num_philosophers > i)
//         {
//             if (settings->philo_status[i] == ONE_DIED)
//                 settings->funeral = ONE_DIED;
//             if (settings->philo_status[i] == FULL)
//                 settings->all_full--;
//             i++;
//         }
//         safe_mutex(settings->t_common_status_mtx, UNLOCK);
//         usleep(100000);
//     }
// }
