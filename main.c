
#include "philo.h"
#include <sys/time.h>

// static void show_forks(t_settings *settings)
// {

//   safe_mutex(settings->t_write_mtx, LOCK);
//   for (int i = 0; i <= settings->num_philosophers+ 30; i++)
//   {
//     printf("\n[%d] philo[%ld] philosophers[i].fork_prev = %ld", i,settings->philosophers[i].philo_id, (long)settings->philosophers[i].fork_prev);
//     printf("\n[%d] philo[%ld] philosophers[i].fork_next = %ld", i,settings->philosophers[i].philo_id, (long)settings->philosophers[i].fork_next);
//     printf("\n[%d] philo[%ld] philosophers[i]second_.for = %ld",i,settings->philosophers[i].philo_id,  (long)settings->philosophers[i].second_fork);
//     printf("\n[%d] philo[%ld] philosophers[i].first_fork = %ld",i,settings->philosophers[i].philo_id,  (long)settings->philosophers[i].first_fork);
//     printf("\n*******************************************************");
// settings->philosophers[i].fork_prev == settings->philosophers[settings->num_philosophers - 1].fork_next)
//       printf("\n[%ld]dYEEES" , settings->philosophers->philo_id);
//     if (settings->philosophers[i].first_fork == settings->philosophers[settings->num_philosophers - 1].first_fork)
//       printf("\n[%ld]dALSO" , settings->philosophers->philo_id);
//     printf("\n*******************************************************");
//     if (
// }
//   safe_mutex(settings->t_write_mtx, UNLOCK);
// }

int main(int argc, char const *argv[])
{
  (void)argc;
  (void)argv;

  const char *test[] = {"0", "9", "5500", "200", "250", "15"};
  t_settings *settings;
  settings = ft_calloc(1, sizeof(t_settings));

  if (argc == 5 || argc == 6)
    parse_argv(settings, argv);
  // for testing
  if (argv == NULL)
    parse_argv(settings, test);
  else
    parse_argv(settings, argv);

  load_settings(settings, argv);
  create_mutexes(settings);
  create_philos(settings);
  if (TEST)
  {
    usleep(3500);
    create_maitre(settings);
  }
 // check_mutex(settings, "settings->maitre->meal_mtx", settings->maitre->meal_mtx, "settings>meal_mtx", settings->meal_mtx, &settings->philosophers[3]);

  join_threads(settings);

  // support_read_returns(settings);

  //  i = 0;
  //   while (settings->num_philosophers > i++)
  //       pthread_join(settings->philosophers[i].thread_id, NULL);
  // sleep(2);
  // if (settings->all_full == 0)
  //           exit(EXIT_SUCCESS);
  // exiting(settings, SUCCESS);
  // i could actually catch the return
  return 0;
}
