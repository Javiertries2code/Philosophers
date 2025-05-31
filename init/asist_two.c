#include "../philo.h"

void	create_assitant_two(t_settings *s)
{
	t_asist	*asist;

	asist = kloc(1, sizeof(t_asist));
	s->nd_asist = asist;
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
	pthread_create(&asist->th_asist, NULL, &rout_nd_asistant, (void *)asist);
}

void	*rout_nd_asistant(void *args)
{
	t_asist	*asist;

	asist = (t_asist *)args;
	busy_wait_start(asist->synchro_t, PHILO_HEAD_START);
	asistant_monitor(asist, 1, 1);
	return (NULL);
}
