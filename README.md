
LAS DAY
for some reasosn that i dont get, it fails when creatinf mutexes to access t_time, i couls use those from write mtx

gotta make order in the delaying think, taking it out in another function, no need of thread protection

#Midnight ideas

-- For sinchronuous starting:
        -Right at the begining of the philo thread routine iw will busy-wait

            while (1)
                {
                if(seetings->start_simulation != 0)
                    break
                }

        -Then, in the funcioton running the simulation.

            setting->start_simulation = (get_current_time);
            witing fucntion("simualtion started) //with a thread safe
                LOCK
                write(str)
                UNLOCK

        -I assume this way all threads will start exact same moment

--For the the number of meals, it makes sense to simply do a reverse conter
 
  if (simulation_finished) \\thats a bool type
    exit();

  if (max_meals == 0)
    {
        writing_function("is full")
        exit();
    }

-- in case of recreating the safe thread handlers and error functions, locking write, printing error and exiting makes sense.

--At the same time the monitor checks for a a died philo, he could check for a full filo. though exiting is a posibility, a long sleeeping is a possibility.
after waiting for the pthreadJOIN, NULLING the pointer and the phil could be a thing


***tips

busy waiting
while (condition)
; <--- enough with semicolom


-- In case of only one philo, it could be create a different routine, all sequencial, while (number of meals != 0) {
calculate the thinking time, printing data, and go ahead.}
 Afther pthread join


==2466232==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000028 (pc 0x5e8348a41c46 bp 0x75a0a20fadd0 sp 0x75a0a20fad10 T5)
==2466232==The signal is caused by a READ memory access.
==2466232==Hint: address points to the zero page.
    #0 0x5e8348a41c46 in routine_ph simulation/simulation.c:15
    #1 0x75a0a7494ac2 in start_thread nptl/pthread_create.c:442
    #2 0x75a0a752684f  (/lib/x86_64-linux-gnu/libc.so.6+0x12684f)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV simulation/simulation.c:15 in routine_ph
Thread T5 created by T0 here:
    #0 0x75a0a7858685 in __interceptor_pthread_create ../../../../src/libsanitizer/asan/asan_interceptors.cpp:216
    #1 0x5e8348a41559 in create_philos init/init.c:71
    #2 0x5e8348a406ee in main /home/havr/Desktop/Philo/philo/main.c:20
    #3 0x75a0a7429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

==2466232==ABORTING
