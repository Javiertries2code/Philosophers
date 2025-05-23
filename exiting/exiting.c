#include "../philo.h"

static void	free_allocated(t_settings *s)
{
	free(s->t_write_mtx);
	free(s->time_mtx);
	free(s->mtr_mtx);
	free(s->printer_mtx);
	free(s->funeral_mtx);
	free(s->st_mtx);
	free(s->meal_mtx);
	free(s->philo_status);
	free(s->ret_st);
	free(s->philos);
	free(s->mutexes);
	free(s->mtr);
	free(s->feed_mtx);
	free(s);
}

static void	destroy_mutexes(t_settings *s)
{
	int	i;

	i = 0;
	if (s->t_write_mtx)
		pthread_mutex_destroy(s->t_write_mtx);
	if (s->time_mtx)
		pthread_mutex_destroy(s->time_mtx);
	if (s->mtr_mtx)
		pthread_mutex_destroy(s->mtr_mtx);
	if (s->printer_mtx)
		pthread_mutex_destroy(s->printer_mtx);
	while (i < s->num_ph)
	{
		pthread_mutex_destroy(&s->mutexes[i]);
		pthread_mutex_destroy(&s->st_mtx[i]);
		pthread_mutex_destroy(&s->meal_mtx[i]);
		pthread_mutex_destroy(&s->funeral_mtx[i]);
		i++;
	}
}

void	free_memory(t_settings *s)
{
	if (!s)
		return ;
	destroy_mutexes(s);
	free_allocated(s);
}

void	exit_on_error(char *str)
{
	write(2, "ERROR\n", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	exiting(t_settings *settings, char *str)
{
	if (str != NULL)
		exit_on_error(str);
	free_memory(settings);
	exit(SUCCESS);
}
