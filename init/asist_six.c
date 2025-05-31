#include "../philo.h"


void	create_assitant_six(t_settings *s)
{
	t_asist	*asist;

	asist = kloc(1, sizeof(t_asist));
	s->sixth_asist = asist;
	asist->set = s;
	asist->meal_mtx = s->meal_mtx;
	asist->own_death = s->own_death;
	asist->any_death = &s->any_death;
	asist->own_death_mtx = s->own_death_mtx;
	asist->any_death_mtx = s->any_death_mtx;
	asist->status_mtx = s->st_mtx;
	asist->write_mtx = s->t_write_mtx;
	asist->feed_mtx = s->feed_mtx;
	asist->num_philosophers = s->num_ph;
	asist->philos = s->philos;
	asist->ret_st = s->ret_st;
	asist->threshold = s->threshold;
	asist->synchro_t = get_time(&s->synchro_t, CHANGE, MILI);
	pthread_create(&asist->th_asist, NULL, &rout_three_back, (void *)asist);
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
						printf("%ld %d died\n", time, i +1);

						*asist->any_death = ONE_DIED;	
					}
					safe_mutex(asist->any_death_mtx, UNLOCK);
				//	printf("%ld %d died\n", time, i +1);
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

