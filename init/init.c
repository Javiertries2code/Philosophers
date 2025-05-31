#include "../philo.h"

void	create_mutexes(t_settings *s)
{
	int	i;

	i = 0;
	s->t_write_mtx = kloc(1, sizeof(pthread_mutex_t));
	s->mtr_mtx = kloc(1, sizeof(pthread_mutex_t));
	s->time_mtx = kloc(1, sizeof(pthread_mutex_t));
	s->feed_mtx = kloc(1, sizeof(pthread_mutex_t));
	s->printer_mtx = kloc(1, sizeof(pthread_mutex_t));
	s->funeral_mtx = kloc(s->num_ph, sizeof(pthread_mutex_t));
	s->mutexes = kloc(s->num_ph, sizeof(pthread_mutex_t));
	s->st_mtx = kloc(s->num_ph, sizeof(pthread_mutex_t));
	s->meal_mtx = kloc(s->num_ph, sizeof(pthread_mutex_t));
	s->any_death_mtx = kloc(1, sizeof(pthread_mutex_t));
	s->own_death_mtx = kloc(s->num_ph, sizeof(pthread_mutex_t));
	while (i < (int)(s->num_ph))
	{
		safe_mutex(&s->mutexes[i], INIT);
		safe_mutex(&s->st_mtx[i], INIT);
		safe_mutex(&s->meal_mtx[i], INIT);
		safe_mutex(&s->funeral_mtx[i], INIT);
		safe_mutex(&s->own_death_mtx[i], INIT);
		i++;
	}
	safe_mutex(s->t_write_mtx, INIT);
	safe_mutex(s->time_mtx, INIT);
	safe_mutex(s->mtr_mtx, INIT);
	safe_mutex(s->any_death_mtx, INIT);
}

static void	init_philo_data(t_settings *s, long int i)
{
	t_philo	*philo;

	philo = &s->philos[i];
	philo->ph_id = i + 1;
	philo->tt_die = s->tt_die;
	philo->time_to_eat = s->tt_eat;
	philo->time_to_sleep = s->tt_sleep;
	philo->num_ph = s->num_ph;
	philo->settings = s;
	philo->max_meals = s->max_meals;
	philo->wrt_mtx = s->t_write_mtx;
	philo->time_mtx = s->time_mtx;
	philo->threshold = s->threshold;
	philo->synchro_t = get_time(&s->synchro_t, CHANGE, MILI);
	philo->status_mtx = &s->st_mtx[i];
	////
	philo->own_death_mtx = &s->own_death_mtx[i];
	philo->any_death_mtx = s->any_death_mtx;
	///
	philo->own_death = &s->own_death[i];
	philo->any_death = &s->any_death;
	////
	philo->meal_mtx = &s->meal_mtx[i];
	s->philos[i].return_status = &s->ret_st[i];
	philo->fork_next = &s->mutexes[i];
	philo->last_meal = get_milisec(NULL, GET, MILI);
	philo->funeral = &(s->funeral);
	philo->funeral_mtx = s->funeral_mtx;
	philo->printer = &(s->printer);
	philo->prntr_mtx = s->printer_mtx;
}

static void	assign_forks(t_settings *s, long int i)
{
	t_philo	*philo;

	philo = &s->philos[i];
	if (i == 0)
		philo->fork_prev = &s->mutexes[s->num_ph - 1];
	else
		philo->fork_prev = &s->mutexes[i - 1];
	if (philo->ph_id % 2 == 0)
	{
		philo->first_fork = philo->fork_next;
		philo->second_fork = philo->fork_prev;
	}
	else
	{
		philo->second_fork = philo->fork_next;
		philo->first_fork = philo->fork_prev;
	}
}

void	create_philos(t_settings *s)
{
	long int	i;

	i = 0;
	s->philos = kloc(s->num_ph, sizeof(t_philo));
	while (i < s->num_ph)
	{
		init_philo_data(s, i);
		assign_forks(s, i);
		pthread_create(&s->philos[i].thread_id, NULL, &routine_ph,
			(void *)&s->philos[i]);
		i++;
	}
}
