#include "../philo.h"

void	set_threshold(t_settings *settings)
{
	long	current;
	long	start;
	long	max_sleep;
	int		i;

	settings->max_thr = 0;
	settings->threshold = 0;
	if (settings->tt_eat >= settings->tt_die)
		max_sleep = settings->tt_eat;
	else
		max_sleep = settings->tt_die;
	i = 0;
	while (i < THRESHOLD_TEST_ITERATION)
	{
		start = get_microsec();
		usleep(max_sleep);
		current = get_microsec();
		settings->max_thr = current - start - (long)max_sleep;
		if (settings->max_thr > settings->threshold)
			settings->threshold = settings->max_thr;
		i++;
	}
	funcion_proporcional(settings);
}

void	funcion_proporcional(t_settings *settings)
{
	float	input_min;
	float	input_max;
	float	output_min;
	float	output_max;
	float	input;
	float	output;

	input_min = THRESHOLD_MIN_INPUT;
	if (SLEEPING_THRESHOLD_TESTTIME != 0)
		input_max = SLEEPING_THRESHOLD_TESTTIME;
	else
		input_max = settings->max_thr;
	output_min = MIN_SAFETY_MARGIN;
	output_max = MAX_SAFETY_MARGIN;
	input = (float)settings->threshold;
	if (input < input_min)
		input = input_min;
	else if (input > input_max)
		input = input_max;
	output = ((input - input_min) / (input_max - input_min))
		* (output_max - output_min) + output_min;
	settings->threshold *= output;
}

void	precise_sleep(long nap_time, long *threshold)
{
	long	start;

	*threshold = 0;
	start = get_milisec();
	if (nap_time > *threshold)
		usleep(nap_time - *threshold);
	while (get_milisec() - start < nap_time)
		;
}
