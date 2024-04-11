#include "../philo.h"

///this seems to be ok, i gotta check it out

long get_microsec()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return ((long)tv.tv_sec * 1e6 + tv.tv_usec);
}

void precise_sleep(long nap_time, long *threshold)
{
long start;

start = get_microsec();
usleep(nap_time - *threshold);

while (get_microsec()- start < nap_time)
	;
//printf("diff precise = %ld\n", get_microsec()- start );
}

 int main(int argc, char const *argv[])
 {
  
  long naptime = 30000;
  long num = 450;
  long start;

start = get_microsec();

for(int i = 0; i < 10; i++)
  {
    start = get_microsec();

    precise_sleep(naptime, &num);

  printf("diff main= %ld\n", get_microsec()- start );}

    return 0;
 }
 