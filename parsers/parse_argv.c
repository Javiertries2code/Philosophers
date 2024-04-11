#include "../philo.h"
/**
 * @brief here the args are parsed, and if all good
 * it  call loads the settings struct
 * @see oad_settings
 * @param settings struct with general info common to every users
 * @param argv well! Our old good friend argv
 */
void parse_argv(t_settings *settings, const char *argv[])
{    write(1,"into parseargv\n",16);
(void)argv;
(void)settings;
    //parse_int(argv);
    //this parser sucks, better doing it  before the exam
      //settings = ft_calloc(1, sizeof(t_settings)); 
    
}

// int parse_int(char *argv[])
// {
//   int i;
//   int j;
//    write(1,"into pars_int\n",14);

//   i = 1;
//   j = 0;
//   while(argv[i])
//   {
//     if (atol(argv[i]) > INT_MAX || atol(argv[i]) <= 0)
//       exit_on_error();
//     while(argv[i][j] != '\0')
//     {printf("i = %d\n j = %d \n", i, j);
//       if( argv[i][j] && (argv[i][j] < '0' || argv[i][j] > '9'))
//         exit_on_error();
//       else
//       j++;
//     }
//     j = 0;
//     i++;
//   }
// }