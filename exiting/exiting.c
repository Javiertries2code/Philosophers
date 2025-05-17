#include "../philo.h"

static void	free_allocated(t_settings *s)
{
	free(s->t_write_mtx);
	free(s->time_mtx);
	free(s->t_maitre_mtx);
	free(s->printer_mtx);
	free(s->funeral_mtx);
    free(s->status_mtx);
	free(s->meal_mtx);
    free(s->philo_status);
	free(s->return_status);
	free(s->philosophers);
     free(s->mutexes);
     free(s->maitre);
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
	if (s->t_maitre_mtx)
		pthread_mutex_destroy(s->t_maitre_mtx);
	if (s->printer_mtx)
		pthread_mutex_destroy(s->printer_mtx);
	while (i < s->num_philosophers)
	{
		pthread_mutex_destroy(&s->mutexes[i]);
		pthread_mutex_destroy(&s->status_mtx[i]);
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
