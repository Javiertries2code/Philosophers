#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <limits.h>
# include <errno.h>


// color codes for diferent states, use like
//
#define RESET "\033[0m"     /* Reset to default color */
#define RED "\033[1;31m"    /* Bold Red */
#define GREEN "\033[1;32m"  /* Bold Green */
#define YELLOW "\033[93m" /* Bold Yellow */
#define BLUE "\033[1;34m"   /* Bold Blue */
#define PINK "\033[1;35m"   /* Bold Magenta */
#define CYAN "\033[1;36m"   /* Bold Cyan */
#define WHITE "\033[1;37m"  /* Bold White */

#define ERROR 1
#define SUCCESS 0
//ALive 
#define ALIVE   0
//All alive will be 0
//every full philo will add 1
//any death will set to 10:
// so status = 0 -> all alive
// status  = 5 -> all full
// status> 5 -> anyone is death


/**
 * @brief for timin purposses, to start sinchronisation, an starting time synchro_t in the struct
 *  is defined. but the diferrence must be calculated and removed from a sandclock time, for a synchronous
 * begining time to wait for begining = sand_clock - (current time - synchro_t);
 * 
 */
#define SAND_CLOCK 300
//delay to give time to set the synchro sign
#define SLEEP_TO_SYNCHRO 10000
//used to test the thresold, 
//chaged later into using the maximun of the inputs
#define SLEEPING_THRESHOLD_TESTTIME 0
#define THRESHOLD_TEST_ITERATION   100
#define THRESHOLD_MIN_INPUT   150
#define MIN_SAFETY_MARGIN     1.4
#define MAX_SAFETY_MARGIN     1.9
#define USLEEP_GAP               50//trimmed for test 

#define NO_MAX_MEALS            -1
#define ALL_ALIVE               0
#define ONE_DIED                1
#define FULL                    2


typedef pthread_mutex_t *write_mtx;
typedef pthread_mutex_t *time_mtx;
typedef pthread_mutex_t *t_maitre_mtx;
typedef pthread_mutex_t *t_general;
typedef pthread_mutex_t *t_status_mtx;
typedef struct timeval timeval;

//Notice either FED and FULL got same 2 number, to avoid mistakes
typedef enum s_states
{
    EATING,
    SLEEPING,
    FED,
    THINKING,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DEATH
    
} t_states;

typedef enum timing_options{
   
    MILISECONDS,
    MICROSECONDS,
    CHANGE,
    GET

} timing_options;

typedef enum mtx_option
{
    INIT,
    LOCK,
    UNLOCK,
    DESTROY

} t_mtx_option;

typedef struct s_settings
{
     long int num_philosophers;
     long int time_to_eat;
     long int time_to_sleep;
     long int max_meals;
     long int time_to_die;
    long threshold;
    int status;
    float safety_margin;
    long max_thr;
    /// @brief one array, one for every philo
    int *philo_status;

    int funeral;
    int all_full;
    int **return_status;
    //array fo mutexes, one for every fork, prev and next
    //for every hpilo. as statucs for every philo
    pthread_mutex_t *mutexes;
    pthread_mutex_t *status_mtx;
    // maitre might not be neccesary anymore
    t_maitre_mtx t_maitre_mtx;
    write_mtx write_mtx;
    time_mtx time_mtx;
    t_general t_funeral_mtx;

    t_status_mtx    t_status_mtx;

    struct timeval synchro_t;
    struct s_philo *philosophers;
    struct s_maitre *maitre;

} t_settings;

typedef struct s_philo
{

    t_settings *settings;
    long int philo_id;
    pthread_t thread_id;

    long int time_to_die;
    long int time_to_eat;
    long int time_to_sleep;
    long threshold;

    pthread_mutex_t *fork_next;
    pthread_mutex_t *fork_prev;
    write_mtx write_mtx;
    time_mtx time_mtx;
    time_mtx t_status_mtx;
    t_general t_general;
    int *status;
    long synchro_t;

} t_philo;

typedef struct s_maitre
{
    pthread_t th_maitre;
    t_settings *settings;

} t_maitre;

// simulation
void *routine_ph(void *args);
void *routine_maitre(void *args);
 int routine_even( t_philo *philo);
 int routine_odd( t_philo *philo);
void check_deaths(t_settings *settings);
 void support_read_returns(t_settings *settings);
 


// parsers
void parse_argv(t_settings *settings, const char *argv[]);
int parse_int(char *argv[]);

// init
void load_settings(t_settings *settings, const char *argv[]);
void create_philos(t_settings *settings);
void create_maitre(t_settings *settings);

void create_mutexes(t_settings *settings);
void join_threads(t_settings *settings);

//timing
void set_threshold(t_settings *settings);
long time_microsec(timeval *tv);
long to_microsec(timeval *tv);
long get_microsec();
void precise_sleep(long nap_time, long *threshold);
void funcion_proporcional(t_settings *settings);
long get_mili_sec();
long	get_mili_sec();
long get_time(timeval *tv, timing_options operation, timing_options units);
//delaying
void calculate_delay(struct timeval *delay, struct timeval synchro_t, write_mtx write_mtx);
void delay_to_syncro(long *delay, long* synchro_t, write_mtx write_mtx);


//handers
void init_error( int error_return);
void lock_error( int error_return);
void destroy_error( int error_return);
 void safe_mutex(pthread_mutex_t *mtx, t_mtx_option option);
 void unlock_error( int error_return);




// utils

void *ft_calloc(size_t count, size_t size);
void ft_bzero(void *s, size_t n);
size_t ft_strlen(const char *s);
void write_function(t_settings *settings, char *str);



// exiting
void exiting(t_settings *settings, char *str );
void free_memory(t_settings *settings);
void exit_on_error(char * str);
 void free_allocated_items();


// supoort
void print_data(t_settings *settings, char *str);

#endif