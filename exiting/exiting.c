#include "../philo.h"

void free_memory(t_settings *settings)
{
free(settings->philosophers);
free(settings->mutexes);
free(settings);
}

void exiting(t_settings *settings, int flag){
if (flag == ERROR)
    exit_on_error(settings);
else
    free_memory(settings);
}

void exit_on_error(){
    write(2,"Error\n", 6);
        exit(1);
}