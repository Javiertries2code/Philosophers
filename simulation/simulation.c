#include "../philo.h"

void	*set_all_died(t_maitre *maitre)
{
	int	i;

	i = 0;
	while (maitre->num_philosophers > i)
	{
		safe_mutex(&maitre->status_mtx[i], LOCK);
		maitre->return_status[i] = ONE_DIED;
		safe_mutex(&maitre->status_mtx[i], UNLOCK);
		i++;
	}
	return (NULL);
}

void	*routine_maitre(void *args)
{
	t_maitre	*maitre;
	long int	i;
	int			run;
	int			var_status;

	run = 1;
	maitre = (t_maitre *)args;
	busy_wait_start(maitre->synchro_t, PHILO_HEAD_START);
	 usleep(1);//sleep, else settingt timing, or philo or smthing is not created yet, 
	 //and delivers shity value
	while (run)
	{
		safe_mutex(maitre->funeral_mtx, LOCK);
		safe_mutex(maitre->printer_mtx, LOCK);
		i = 0;
		while (maitre->num_philosophers > i)
		{
			safe_mutex(&maitre->status_mtx[i], LOCK);
			var_status = maitre->return_status[i];
			safe_mutex(&maitre->status_mtx[i], UNLOCK);
			// ///////////TEST
				// safe_mutex(maitre->settings->t_write_mtx, LOCK);
				// printf("%ld [%ld] timeleft%s\n", time_left(&maitre->settings->philosophers[i]), i + 1, RESET);
				// safe_mutex(maitre->settings->t_write_mtx, UNLOCK);
			// ///TEST
			// //			if (var_status == ONE_DIED || time_left(&maitre->settings->philosophers[i + 1]) <= 0)

			//if (var_status == ONE_DIED )
			if (var_status == ONE_DIED || time_left(&maitre->settings->philosophers[i]) <= 0)
			{
				// printer(&maitre->settings->philosophers[i], DIED);
				safe_mutex(maitre->settings->t_write_mtx, LOCK);
				printf("%s%ld %ld died%s\n", CYAN, (get_milisec()
						- maitre->settings->starting_time), i + 1, RESET);
				safe_mutex(maitre->settings->t_write_mtx, LOCK);
				*maitre->printer = 1;
				*maitre->funeral = 1;
				set_all_died(maitre);
				safe_mutex(maitre->printer_mtx, UNLOCK);
				 safe_mutex(maitre->funeral_mtx, UNLOCK);
				 run = 0;
			}
			else
				i++;
		}
		safe_mutex(maitre->printer_mtx, UNLOCK);
		safe_mutex(maitre->funeral_mtx, UNLOCK);
		
	}
	return (NULL);
}

void	*routine_ph(void *args)
{
	t_philo	*philo;
	int		*ret;

	// struct timeval delay;
	// long delay_to_sync;
	philo = (t_philo *)args;
	safe_mutex(philo->status_mtx, LOCK);
	ret = philo->return_status;
	safe_mutex(philo->status_mtx, UNLOCK);
	busy_wait_start(philo->synchro_t, 0);
	if (philo->settings->starting_time == 0)
		philo->settings->starting_time = get_time(NULL, GET, MILISECONDS);
	safe_mutex(philo->time_mtx, LOCK);
	philo->last_meal = get_time(NULL, GET, MILISECONDS);
	safe_mutex(philo->time_mtx, UNLOCK);
	//////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
	// safe_mutex(philo->settings->t_write_mtx, LOCK);
	// printf(RED "Philo[%ld] starts simulation=  %ld\n " RESET, philo->philo_id,
	// 	(get_milisec() - philo->settings->starting_time));
	// safe_mutex(philo->settings->t_write_mtx, UNLOCK);
	//////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
	if (philo->philo_id % 2 == 0)
	{
		routine_even(philo);
	}
	else
	{
		routine_odd(philo);
	}
	//////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
	safe_mutex(philo->t_write_mtx, LOCK);
	printf(PINK "routine_ph \nphilo [%d] LEAVING DINNER \n" RESET,
		(int)philo->philo_id);
	printf(WHITE "philo [%d] \n return (status = %d\n" RESET,
		(int)philo->philo_id, (int)*philo->return_status);
	safe_mutex(philo->t_write_mtx, UNLOCK);
	//////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
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
		ret = eating(philo);
		ret2 = sleeping(philo);
		ret3 = thinking(philo);
		if (ret != 0)
			return (ret);
		if (ret2 != 0)
			return (ret2);
		if (ret3 != 0)
			return (ret3);
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
int	printer(t_philo *philo, char *opt)
{
	char	*colors;
	long	time;

	time = (get_milisec() - philo->settings->starting_time);
	// GET STRCMP FROM LIBFT
	// GET STRCMP FROM LIBFT
	// GET STRCMP FROM LIBFT
	if (!opt)
		return (ALL_ALIVE);
	if (!strcmp(opt, FORK) || !strcmp(opt, FORK2))
		colors = BLUE;
	else if (!strcmp(opt, THINKING))
		colors = YELLOW;
	else if (!strcmp(opt, SLEEPING))
		colors = GREEN;
	else if (!strcmp(opt, DIED))
		colors = RED;
	safe_mutex(philo->printer_mtx, LOCK);
	if (*philo->printer == 1)
	{
		safe_mutex(philo->printer_mtx, UNLOCK);
		return (ONE_DIED);
	}
	safe_mutex(philo->t_write_mtx, LOCK);
	if (!strcmp(opt, FORK2))
	{
		printf("%s%ld %ld has taken a fork%s\n", colors, time, philo->philo_id,
			RESET);
		printf(PINK "%ld %ld %s%s\n", time, philo->philo_id, EATING, RESET);
	}
	else
		printf("%s%ld %ld %s%s\n", colors, time, philo->philo_id, opt, RESET);
	safe_mutex(philo->t_write_mtx, UNLOCK);
	safe_mutex(philo->printer_mtx, UNLOCK);
	if (!strcmp(opt, DIED))
		return (ONE_DIED);
	return (ALL_ALIVE);
}

int	all_alive(t_philo *philo, char *opt)
{
	long	left_life;

	left_life = time_left(philo);
	if (left_life <= 0) // Could trick safe using <=1
	{                   // reusing to save som ml in case of
		left_life = (get_milisec() - philo->settings->starting_time);
		safe_mutex(philo->status_mtx, LOCK);
		// if (*philo->return_status != ONE_DIED){
		// 	printer(philo, DIED);
		// }
		*philo->return_status = ONE_DIED;
		safe_mutex(philo->status_mtx, UNLOCK);
		return (ONE_DIED);
	}
	return (printer(philo, opt));
}
