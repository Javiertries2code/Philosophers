#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <limits.h>

// color codes for diferent states, use like
//
#define RESET "\033[0m"     /* Reset to default color */
#define RED "\033[1;31m"    /* Bold Red */
#define GREEN "\033[1;32m"  /* Bold Green */
#define YELLOW "\033[1;33m" /* Bold Yellow */
#define BLUE "\033[1;34m"   /* Bold Blue */
#define PINK "\033[1;35m"   /* Bold Magenta */
#define CYAN "\033[1;36m"   /* Bold Cyan */
#define WHITE "\033[1;37m"  /* Bold White */

#define ERROR 1
#define SUCCESS 0

typedef pthread_mutex_t *write_mtx;
typedef pthread_mutex_t *maitre;

typedef enum philo_states
{
    EATING,
    SLEEPING,
    THINKING,
    FULL,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DEATH
} t_states;

typedef struct s_settings
{

    long int num_philosophers;
    long int time_to_eat;
    long int time_to_sleep;
    long int max_meals;
    long int time_to_die;
    bool start_simulation;
    bool all_alive;

    pthread_mutex_t *mutexes;
    maitre maitre;
    write_mtx write_mtx;

    struct timeval starting_time;
    struct s_philo *philosophers;

} t_settings;

typedef struct s_philo
{

    t_settings *settings;
    long int philo_id;
    pthread_t thread_id;
    long int time_to_die;
    long int time_to_eat;
    long int time_to_sleep;
    pthread_mutex_t *fork_next;
    pthread_mutex_t *fork_prev;
    write_mtx write_mtx;
    //struct timeval current_time;

} t_philo;

// simulation
void *routine_ph(void *args);

// parsers
void parse_argv(t_settings *settings, const char *argv[]);
int parse_int(char *argv[]);

// utils
void load_settings(t_settings *settings, const char *argv[]);
void create_philos(t_settings *settings);
void create_mutexes(t_settings *settings);
void join_threads(t_settings *settings);

// utils
void *ft_calloc(size_t count, size_t size);
void ft_bzero(void *s, size_t n);

// exiting
void exiting(t_settings *settings, int flag);
void free_memory(t_settings *settings);
void exit_on_error();

// supoort
void print_data(t_settings *settings, char *str);

#endif