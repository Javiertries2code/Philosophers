#include "../philo.h"

void	*set_all_died(t_maitre *maitre)
{
	int	i;

	i = 0;
	while (maitre->num_philosophers > i)
	{
		safe_mutex(&maitre->status_mtx[i], LOCK);
		maitre->ret_st[i] = ONE_DIED;
		safe_mutex(&maitre->status_mtx[i], UNLOCK);
		i++;
	}
	return (NULL);
}

void	*rout_mtr(void *args)
{
	t_maitre	*maitre;
	long int	i;
	int			run;
	int			var_status;
	long int	death_time;

	run = 1;
	maitre = (t_maitre *)args;
	busy_wait_start(maitre->synchro_t, PHILO_HEAD_START);
	usleep(1);
	while (run)
	{
		safe_mutex(maitre->funeral_mtx, LOCK);
		safe_mutex(maitre->printer_mtx, LOCK);
		i = 0;
		while (maitre->num_philosophers > i)
		{
			safe_mutex(maitre->set->feed_mtx, LOCK);
			if (maitre->set->all_full == 0)
				return (NULL);
			safe_mutex(maitre->set->feed_mtx, UNLOCK);
			safe_mutex(&maitre->status_mtx[i], LOCK);
			var_status = maitre->ret_st[i];
			safe_mutex(&maitre->status_mtx[i], UNLOCK);
			if ((var_status == ONE_DIED
					|| (time_left(&maitre->set->philos[i]) <= 0
						&& var_status != FULL)) && *maitre->printer == 0)
			{
				death_time = get_milisec() - maitre->set->starting_time;
				*maitre->printer = 1;
				*maitre->funeral = 1;
				safe_mutex(maitre->set->t_write_mtx, LOCK);
				printf("%s%ld %ld died parse mada%s\n", CYAN, death_time, i + 1,
					RESET);
				safe_mutex(maitre->set->t_write_mtx, UNLOCK);
				set_all_died(maitre);
				safe_mutex(maitre->printer_mtx, UNLOCK);
				safe_mutex(maitre->funeral_mtx, UNLOCK);
				run = 0;
				return (NULL);
			}
			i++;
		}
		safe_mutex(maitre->printer_mtx, UNLOCK);
		safe_mutex(maitre->funeral_mtx, UNLOCK);
	}
	return (NULL);
}

void	*rout_asistant(void *args)
{
	t_asist	*asist;
	bool run;
	int i;
	bool death;

	
	asist = (t_asist *)args;
	busy_wait_start(asist->synchro_t, PHILO_HEAD_START);
	usleep(1);
	 run = true;
	while (run)
	{
		
		i = 0;
		while (asist->num_philosophers > i)
		{				

			safe_mutex(&asist->own_death_mtx[i], LOCK);
			death = asist->own_death[i];
			safe_mutex(&asist->own_death_mtx[i], UNLOCK);

			if (death == true)
			{
			safe_mutex(asist->any_death_mtx, LOCK);
			 *asist->any_death = true;
			safe_mutex(asist->any_death_mtx, UNLOCK);
			
				run = false;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
void	*routine_ph(void *args)
{
	t_philo	*philo;
	int		*ret;

	philo = (t_philo *)args;
	safe_mutex(philo->status_mtx, LOCK);
	ret = philo->return_status;
	safe_mutex(philo->status_mtx, UNLOCK);
	busy_wait_start(philo->synchro_t, 0);
	safe_mutex(philo->time_mtx, LOCK);
	if (philo->settings->starting_time == 0)
		philo->settings->starting_time = get_time(NULL, GET, MILI);
	safe_mutex(philo->time_mtx, UNLOCK);
	safe_mutex(philo->time_mtx, LOCK);
	philo->last_meal = get_time(NULL, GET, MILI);
	safe_mutex(philo->time_mtx, UNLOCK);
	if (philo->ph_id % 2 == 0)
		routine_even(philo);
	else
		routine_odd(philo);
	return (ret);
}

int	routine_even(t_philo *philo)
{
	int	ret;
	int	ret2;
	int	ret3;

	while (1)
	{
		ret2 = sleeping(philo);
		if (ret2 != 0)
			return (ret2);
		ret3 = thinking(philo);
		if (ret3 != 0)
			return (ret3);
		ret = eating(philo);
		if (ret != 0)
			return (ret);
	}
}

int	routine_odd(t_philo *philo)
{
	int	ret;
	int	ret2;
	int	ret3;

	while (1)
	{
		ret3 = thinking(philo);
		if (ret3 != 0)
			return (ret3);
		ret = eating(philo);
		if (ret != 0)
			return (ret);
		ret2 = sleeping(philo);
		if (ret2 != 0)
			return (ret2);
	}
}

static char	*get_color(char *opt)
{
	int	n;

	n = ft_strlen(opt);
	if (!ft_strcmp(opt, FORK, n) || !ft_strcmp(opt, FORK2, n))
		return (BLUE);
	if (!ft_strcmp(opt, THINKING, n))
		return (YELLOW);
	if (!ft_strcmp(opt, SLEEPING, n))
		return (GREEN);
	if (!ft_strcmp(opt, DIED, n))
		return (RED);
	return (WHITE);
}
int	printer(t_philo *philo, char *opt)
{
	long	time;
	long	status;
	bool death;

	status = 0;
 //death = false;

	// time = get_milisec() - philo->settings->starting_time;
	safe_mutex(philo->prntr_mtx, LOCK);
	if (*philo->printer == 1)
	{
		safe_mutex(philo->prntr_mtx, UNLOCK);
		return (ONE_DIED);
	}
	safe_mutex(philo->wrt_mtx, LOCK);
	// trying to make him die on time
	// now it check when about to print, as takingmutexes takes time,
	//	and is just after crossing the mutex u can
	time = get_milisec() - philo->settings->starting_time;
	if (time_left(philo) <= 0)
	{
		safe_mutex(philo->status_mtx, LOCK);
		status = *philo->return_status;
		if (status != ONE_DIED)
		{
			*philo->return_status = ONE_DIED;
			safe_mutex(philo->any_death_mtx, LOCK);
			death = philo->any_death;
			
			safe_mutex(philo->any_death_mtx, UNLOCK);
			if(death == false)
				printf("death false");

			if(death == true){
				printf(CYAN "%ld %ld %s%s in printer with anydeath\n", time, philo->ph_id, DIED,
				RESET);
			safe_mutex(philo->own_death_mtx, LOCK);
			*philo->own_death =true;
			safe_mutex(philo->own_death_mtx, UNLOCK);

			safe_mutex(philo->status_mtx, UNLOCK);
			safe_mutex(philo->wrt_mtx, UNLOCK);
			safe_mutex(philo->prntr_mtx, UNLOCK);
			return ONE_DIED;
			}
			// printf(CYAN "%ld %ld %s%s in printer\n", time, philo->ph_id, DIED,
			// 	RESET);
			safe_mutex(philo->status_mtx, UNLOCK);
			///waiting for maitte to do somthing
			usleep(philo->num_ph * 100);
			///
			safe_mutex(philo->wrt_mtx, UNLOCK);
			safe_mutex(philo->prntr_mtx, UNLOCK);
			return ONE_DIED;
		}
		safe_mutex(philo->status_mtx, UNLOCK);
		//usleep(philo->num_ph * 10000);
		safe_mutex(philo->wrt_mtx, UNLOCK);
		safe_mutex(philo->prntr_mtx, UNLOCK);
		return (ONE_DIED);
	}
	safe_mutex(philo->prntr_mtx, UNLOCK);
	if (!strcmp(opt, FORK2))
	{ // test
		time = get_milisec() - philo->settings->starting_time;
		printf("%s%ld %ld has taken a fork%s\n", get_color(opt), time,
			philo->ph_id, RESET);
		printf(PINK "%ld %ld %s%s\n", time, philo->ph_id, EATING, RESET);
	}
	else
	{ /// test
		time = get_milisec() - philo->settings->starting_time;
		//
		printf("%s%ld %ld %s%s\n", get_color(opt), time, philo->ph_id, opt,
			RESET);
	}
	safe_mutex(philo->wrt_mtx, UNLOCK);
	if (!strcmp(opt, DIED))
		return (ONE_DIED);
	return (ALL_ALIVE);
}

int	all_alive(t_philo *philo, char *opt)
{
	long	left_life;

	left_life = time_left(philo);
	if (left_life <= 0)
	{
		left_life = get_milisec() - philo->settings->starting_time;
		safe_mutex(philo->status_mtx, LOCK);
		*philo->return_status = ONE_DIED;
		safe_mutex(philo->status_mtx, UNLOCK);
		return (ONE_DIED);
	}
	
	return (printer(philo, opt));
}
