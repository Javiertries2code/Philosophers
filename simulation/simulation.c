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


void	*rout_asistant(void *args)
{
	t_asist	*asist;
	bool	run;
	int		i;
	long	time;

	int status; // multiuse
	asist = (t_asist *)args;
	busy_wait_start(asist->synchro_t, PHILO_HEAD_START);
	run = true;
	while (run)
	{
		i = 0;
		while (asist->num_philosophers > i)
		{
			
			if (time_left(&asist->philos[i]) <= 0)
			{
				safe_mutex(&asist->status_mtx[i], LOCK);
				status = asist->ret_st[i];
				safe_mutex(&asist->status_mtx[i], UNLOCK);
				if (status != FULL)
				{
					safe_mutex(asist->write_mtx, LOCK);
					time = get_milisec() - asist->set->starting_time;
					safe_mutex(asist->any_death_mtx, LOCK);
					if (*asist->any_death == ALL_ALIVE){
						printf("%ld %d died", time, i +1);

						*asist->any_death = ONE_DIED;	
					}
					
					safe_mutex(asist->any_death_mtx, UNLOCK);
					//printf("%ld %d died", time, i +1);
					usleep(asist->num_philosophers * 200);
					safe_mutex(asist->write_mtx, UNLOCK);
					return (NULL);
				}
				else
				{
					safe_mutex(asist->feed_mtx, LOCK);
					status = asist->set->all_full;
					safe_mutex(asist->feed_mtx, UNLOCK);
					if (status == 0)
						return (NULL);
				}
			}
			i++;
		}
	}
	return (NULL);
}

void	*rout_nd_asistant(void *args)
{
	t_asist	*asist;
	bool	run;
	int		i;
	long	time;

	int status; // multiuse
	asist = (t_asist *)args;
	busy_wait_start(asist->synchro_t, PHILO_HEAD_START);
	run = true;
	while (run)
	{
		i = asist->num_philosophers -1;
		while (i >= 0)
		{
			
			if (time_left(&asist->philos[i]) <= 0)
			{
				safe_mutex(&asist->status_mtx[i], LOCK);
				status = asist->ret_st[i];
				safe_mutex(&asist->status_mtx[i], UNLOCK);
				if (status != FULL)
				{
					safe_mutex(asist->write_mtx, LOCK);
					time = get_milisec() - asist->set->starting_time;
					safe_mutex(asist->any_death_mtx, LOCK);
						if (*asist->any_death == ALL_ALIVE){
						printf("%ld %d died", time, i +1);

						*asist->any_death = ONE_DIED;	
					}
					safe_mutex(asist->any_death_mtx, UNLOCK);
				//	printf("%ld %d died", time, i +1);
					usleep(asist->num_philosophers * 200);
					safe_mutex(asist->write_mtx, UNLOCK);
					return (NULL);
				}
				else
				{
					safe_mutex(asist->feed_mtx, LOCK);
					status = asist->set->all_full;
					safe_mutex(asist->feed_mtx, UNLOCK);
					if (status == 0)
						return (NULL);
				}
			}
			i--;
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
	int		death;

	death = ALL_ALIVE;
	safe_mutex(philo->wrt_mtx, LOCK);
	// time to print
	time = get_milisec() - philo->settings->starting_time;
	safe_mutex(philo->any_death_mtx, LOCK);
	death = *philo->any_death;
	safe_mutex(philo->any_death_mtx, UNLOCK);
	if (death != ALL_ALIVE)
	{
		//printf(PINK "%ld %ld ya hay funeral%s\n", time, philo->ph_id, RESET);
		safe_mutex(philo->wrt_mtx, UNLOCK);
		return (ONE_DIED);
	}
	else
	{
		if (!strcmp(opt, FORK2))
		{
			// test
			///	time = get_milisec() - philo->settings->starting_time;
			printf("%s%ld %ld has taken a fork%s\n", get_color(opt), time,
				philo->ph_id, RESET);
			printf(PINK "%ld %ld %s%s\n", time, philo->ph_id, EATING, RESET);
		}
		else
		{ /// test
			// time = get_milisec() - philo->settings->starting_time;
			//
			printf("%s%ld %ld %s%s\n", get_color(opt), time, philo->ph_id, opt,
				RESET);
		}
		safe_mutex(philo->wrt_mtx, UNLOCK);
	}
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
