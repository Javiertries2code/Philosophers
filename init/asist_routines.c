#include "../philo.h"


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
			if(!too_short(asist->set))
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
			if(!too_short(asist->set))
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
		}
			i--;
		}
	}
	return (NULL);
}

void	*rout_two_ford(void *args)
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
			if(!too_short(asist->set))
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
					usleep(asist->num_philosophers * 10);
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
		}
			i+=2;
		}
	}
	return (NULL);
}

void	*rout_two_back(void *args)
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
			if(!too_short(asist->set))
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
					usleep(asist->num_philosophers * 10);
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
		}
			i-=2;
		}
	}
	return (NULL);
}

void	*rout_three_ford(void *args)
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
			if(!too_short(asist->set))
			{
			if (time_left(&asist->philos[i]) <= 0  )
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
					usleep(asist->num_philosophers * 10);
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
		}
			i+=3;;
		}
	}
	return (NULL);
}

void	*rout_three_back(void *args)
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
			if(!too_short(asist->set))
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
					usleep(asist->num_philosophers * 10);
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
		}
			i-=3;
		}
	}
	return (NULL);
}
