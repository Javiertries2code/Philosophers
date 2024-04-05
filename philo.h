#ifndef PHILO_H
#define PHILO_H

#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>
#include<sys/time.h>
#include<stdlib.h>


typedef struct s_fork{
long int  fork_id;


} t_fork;

typedef struct s_settings{
    long int num_philosophers;
    long int time_to_eat;
    long int time_to_sleep;
    long int max_meals;
    long int time_to_die;
    // Aint sure if i can malloc memory after a tfork tenedores, like pointing to an array
    //it should work, or perhaps i will have to cast into **
    pthread_mutex_t *mutexes;
    t_fork *tenedores;
    //gotta ask on this one if its going to work
   struct s_philo *philosophers;
} t_settings;

typedef struct s_philo{
t_settings *settings;
long int philo_id;
long int time_to_die;
long int time_to_eat;
long int time_to_sleep;
t_fork *fork_next;
t_fork *fork_prev;
} t_philo;

//parsers
 void parse_argv(t_settings *settings, char *argv[]);

 //utils
void load_settings(t_settings *settings, char *argv[]);
void create_forks( t_settings *settings );
void create_philos(t_settings *settings);
void create_mutexes(t_settings *settings);

//utils
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);



//supoort
void print_data(t_settings *settings);




#endif