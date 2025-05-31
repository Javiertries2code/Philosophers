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


