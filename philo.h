/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:50:58 by jbravo            #+#    #+#             */
/*   Updated: 2025/06/09 22:04:26 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RST "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[93m"
# define BLUE "\033[1;34m"
# define PINK "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

# define ERROR 1
# define SUCCESS 0
# define ALIVE 0
# define DEBUG_MODE 0

# define INPUT_ERROR 1
# define ARG_NEG 2
# define UNVALID_ARG 3
# define ARG_BIG 4
# define ARG_SMALL 5
# define NO_PHILO 6
# define MALLOC 7
# define NO_MEALS 8

# define SAND_CLOCK 1000
# define SLEEP_TO_SYNCHRO 1000
# define PHILO_HEAD_START 10
# define SLEEPING_THRESHOLD_TESTTIME 0
# define WAIT_TO_SYNCHRO 1000
# define THRESHOLD_TEST_ITERATION 50
# define THRESHOLD_MIN_INPUT 150
# define MIN_SAFETY_MARGIN 1.05
# define MAX_SAFETY_MARGIN 1.1
# define USLEEP_GAP 50

# define NO_MAX_MEALS -1
# define ALL_ALIVE 0
# define ONE_DIED 1
# define FULL 2
# define TEST 1
# define ALL_FULL -1

# define EATING "is eating"
# define FORK "has taken a fork"
# define FORK2 "has taken a fork2"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef pthread_mutex_t	*t_funeral_mtx;
typedef pthread_mutex_t	*t_feed_mtx;
typedef pthread_mutex_t	*t_write_mtx;
typedef pthread_mutex_t	*t_tm_mtx;
typedef pthread_mutex_t	*t_maitre_mtx;
typedef pthread_mutex_t	*t_general;
typedef pthread_mutex_t	*t_common_status_mtx;
typedef struct s_maitre	t_maitre;
typedef struct s_philo	t_philo;

typedef enum s_states
{
	EATINGA,
	SLEEPINGA,
	FED,
	THINKINGA,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEATH
}						t_states;

typedef enum e_timing_options
{
	MILI,
	MICRO,
	CHANGE,
	GET
}						t_timing_opt;

typedef enum e_mtx_option
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}						t_mtx_option;

typedef struct s_settings
{
	pthread_mutex_t		*own_death_mtx;
	pthread_mutex_t		*any_death_mtx;
	bool				*own_death;
	int					any_death;
	long				num_ph;
	long				tt_eat;
	long				tt_sleep;
	long				max_meals;
	long				tt_die;
	long				threshold;
	int					status;
	float				safety_margin;
	long				max_thr;
	long				starting_time;
	int					*philo_status;
	int					printer;
	t_feed_mtx			feed_mtx;
	int					all_full;
	int					*ret_st;
	pthread_mutex_t		*mutexes;
	pthread_mutex_t		*st_mtx;
	pthread_mutex_t		*meal_mtx;
	t_write_mtx			t_write_mtx;
	t_tm_mtx			time_mtx;
	struct timeval		synchro_t;
	struct s_philo		*philos;
	struct s_maitre		*maitre;
	struct s_asist		*asist;
	struct s_asist		*nd_asist;
	struct s_asist		*third_asist;
	struct s_asist		*fourth_asist;
	struct s_asist		*fifth_asist;
	struct s_asist		*sixth_asist;
	struct s_asist		*seventh_asist;
	struct s_asist		*eight_asist;
}						t_settings;

typedef struct s_asist
{
	t_tm_mtx			time_mtx;
	pthread_mutex_t		*meal_mtx;
	pthread_mutex_t		*own_death_mtx;
	pthread_mutex_t		*any_death_mtx;
	pthread_mutex_t		*status_mtx;
	t_write_mtx			write_mtx;
	t_feed_mtx			feed_mtx;
	bool				*own_death;
	int					*any_death;
	int					*ret_st;
	pthread_t			th_asist;
	t_settings			*set;
	t_philo				*philos;
	long				synchro_t;
	long				threshold;
	long				delay_to_sync;
	long				num_philosophers;
	long				starting_time;
	long				tt_die;

}						t_asist;

typedef struct s_philo
{
	pthread_mutex_t		*own_death_mtx;
	pthread_mutex_t		*any_death_mtx;
	bool				*own_death;
	int					*any_death;
	t_settings			*settings;
	pthread_t			thread_id;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		*fork_next;
	pthread_mutex_t		*fork_prev;
	pthread_mutex_t		*meal_mtx;
	pthread_mutex_t		*status_mtx;
	t_write_mtx			wrt_mtx;
	t_tm_mtx			time_mtx;
	long				*starting_time;
	t_general			t_general;
	int					*printer;
	pthread_mutex_t		*prntr_mtx;
	long				num_ph;
	long				ph_id;
	long				tt_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				last_meal;
	long				max_meals;
	int					*return_status;
	long				threshold;
	long				synchro_t;
	int					*status;
	pthread_mutex_t		*one_death_mtx;
}						t_philo;

typedef struct s_maitre
{
	pthread_t			th_maitre;
	t_settings			*set;
	pthread_mutex_t		*status_mtx;
	pthread_mutex_t		*meal_mtx;
	t_write_mtx			write_mtx;
	t_tm_mtx			time_mtx;
	t_philo				*philos;
	int					*ret_st;
	long				synchro_t;
	long				threshold;
	long				delay_to_sync;
	int					*printer;
	pthread_mutex_t		*printer_mtx;
	long				num_philosophers;
	pthread_mutex_t		*own_death_mtx;
	pthread_mutex_t		*any_death_mtx;
	bool				*own_death;
	int					*any_death;
}						t_maitre;

/* assistants */
void					create_assitant_seven(t_settings *s);
void					*rout_four_ford(void *args);
void					create_assitant_eight(t_settings *s);
void					*rout_four_back(void *args);
void					create_assitants(t_settings *s);
void					create_assitant_one(t_settings *s);
void					create_assitant_two(t_settings *s);
void					create_assitant_three(t_settings *s);
void					create_assitant_four(t_settings *s);
void					create_assitant_five(t_settings *s);
void					create_assitant_six(t_settings *s);
void					*rout_asistant(void *args);
void					*rout_nd_asistant(void *args);
void					*rout_two_ford(void *args);
void					*rout_two_back(void *args);
void					*rout_three_ford(void *args);
void					*rout_three_back(void *args);
void					asistant_monitor(t_asist *a, int step, int rev);
int						check_philo_state(t_asist *a, int i);
int						handle_philo_death(t_asist *asist, int i);

/* core logic */
void					*routine_ph(void *args);
int						routine_even(t_philo *ph);
int						routine_odd(t_philo *ph);
int						eating(t_philo *ph);
int						sleeping(t_philo *ph);
int						thinking(t_philo *ph);
int						all_alive(t_philo *ph, char *opt);
char					*get_col(char *opt);
int						printer(t_philo *ph, char *opt);

/* setup */
int						parse_input(t_settings *s, const char **av);
int						parse_int(char *av[]);
void					load_settings(t_settings *s, const char **av);
void					create_philos(t_settings *s);
void					create_mutexes(t_settings *s);
void					join_threads(t_settings *s);
long					ft_atol(const char *str);

/* time */
long					get_microsec(void);
long					get_milisec(void);
long					get_time(struct timeval *tv, t_timing_opt o,
							t_timing_opt u);
long					to_microsec(struct timeval *tv);
void					busy_wait_start(long s, int h);
void					precise_sleep(long t, long *thr);
long					time_left(t_philo *ph);
bool					too_short(long starting_time, long tt_die);
void					set_threshold(t_settings *s);

/* utils */
void					ft_bzero(void *s, size_t n);
void					*kloc(size_t c, size_t s);
size_t					ft_strlen(const char *s);
int						ft_strcmp(const char *s1, const char *s2, size_t n);
void					write_function(t_settings *s, char *str);
void					safe_mutex(pthread_mutex_t *m, t_mtx_option o);

/* exit */
void					exiting(t_settings *s, char *str);
void					free_memory(t_settings *s);
void					exit_on_error(char *str);
void					free_allocated_items(void);

/* debug */
void					support_read_returns(t_settings *s);
void					print_data(t_settings *s, char *str);

/* error */
int						print_error(int err);
void					init_error(int ret);
void					lock_error(int ret);
void					unlock_error(int ret);
void					destroy_error(int ret);

#endif
