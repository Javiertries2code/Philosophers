#include "../philo.h"

void	create_assitants(t_settings *set)
{
	create_assitant_one(set);
	if (set->num_ph > 20 && set->num_ph <= 39)
		create_assitant_two(set);
	if (set->num_ph > 40 && set->num_ph <= 80)
	{
		create_assitant_three(set);
		create_assitant_four(set);
	}
	if (set->num_ph > 80)
	{
		create_assitant_five(set);
		create_assitant_six(set);
	}
}

void	create_assitant_one(t_settings *s)
{
	t_asist	*asist;

	asist = kloc(1, sizeof(t_asist));
	s->asist = asist;
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
	pthread_create(&asist->th_asist, NULL, &rout_asistant, (void *)asist);
}
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
void	create_assitant_three(t_settings *s)
{
	t_asist	*asist;

	asist = kloc(1, sizeof(t_asist));
	s->third_asist = asist;
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
	pthread_create(&asist->th_asist, NULL, &rout_two_ford, (void *)asist);
}
void	create_assitant_four(t_settings *s)
{
	t_asist	*asist;

	asist = kloc(1, sizeof(t_asist));
	s->fourth_asist = asist;
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
	pthread_create(&asist->th_asist, NULL, &rout_two_back, (void *)asist);
}
void	create_assitant_five(t_settings *s)
{
	t_asist	*asist;

	asist = kloc(1, sizeof(t_asist));
	s->fifth_asist = asist;
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
	pthread_create(&asist->th_asist, NULL, &rout_three_ford, (void *)asist);
}
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
