
#include<stdio.h>
#include<unistd.h>
#include <sys/time.h> 

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"


#define COMIENDO RED
#define DURMIENDO GREEN
#define PENSANDO    CYAN


int main(int argc, char** argv)
{

(void)argc;
(void)argv;

 struct timeval tv;
  struct timeval tv2;


gettimeofday(&tv, NULL);
sleep(1);
gettimeofday(&tv2, NULL);

printf(RED"%ld\n"RESET, tv.tv_sec);

printf(RED"%ld\n"RESET, tv.tv_usec);


printf(GREEN"%ld\n"RESET, tv2.tv_sec);

printf(GREEN"%ld\n"RESET, tv2.tv_usec);


printf(CYAN"%ld\n"RESET, tv2.tv_sec-tv.tv_sec);

printf(CYAN"%ld\n"RESET,tv2.tv_usec - tv.tv_usec);
    
    return 0;
}
