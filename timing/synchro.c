#include "../philo.h"

void	busy_wait_start(long synchro, int head_start)
{
	while (get_milisec() < synchro + SAND_CLOCK + head_start)
		;
}
