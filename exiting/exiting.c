#include "../philo.h"

void free_memory(t_settings *settings)
{
free_allocated_items();
free(settings->philosophers);
free(settings->mutexes);
free(settings);
}

void exiting(t_settings *settings, char *str ){
if (str)
    exit_on_error(str);
else
    free_memory(settings);
}

void exit_on_error(char *str){
    write(2,"str\n", ft_strlen(str) + 1);
        exit(EXIT_FAILURE);
}

 void free_allocated_items()
{
    printf("liberar elemento mallocados dentro de los structs");
}
