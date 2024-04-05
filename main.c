
#include "philo.h"
#include <sys/time.h> 
int main(int argc, char const *argv[])
{
  (void)argc;
  (void)argv;
  char *test[] = {"0", "5", "200", "200", "5"};
  t_settings *settings;
  if (argc == 5 || argc == 6)
      parse_argv(settings, (char **)argv);
//for testing
parse_argv(settings, test);

  
return 0;
}
