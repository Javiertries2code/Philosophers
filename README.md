
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

avr@T:~/Desktop/Philo/philo$ valgrind --tool=helgrind ./filo
==8475== Helgrind, a thread error detector
==8475== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==8475== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==8475== Command: ./filo
==8475== 
INICIO
into parseargv
into load setting
some load setting
in create mutexes
in create philosos num philold 5
MAIN LOCKS MUTEX
MAIN UNLOCKS MUTEX==8475== 
==8475== Process terminating with default action of signal 11 (SIGSEGV)
==8475==  Access not within mapped region at address 0x10
==8475==    at 0x490BEF4: pthread_mutex_lock@@GLIBC_2.2.5 (pthread_mutex_lock.c:80)
==8475==    by 0x4850C66: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==8475==    by 0x109FFF: routine_ph (simulation.c:16)
==8475==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==8475==    by 0x4908AC2: start_thread (pthread_create.c:442)
==8475==    by 0x4999A03: clone (clone.S:100)
==8475==  If you believe this happened as a result of a stack
==8475==  overflow in your program's main thread (unlikely but
==8475==  possible), you can try to increase the size of the
==8475==  main thread stack using the --main-stacksize= flag.
==8475==  The main thread stack size used in this run was 8388608.
==8475== 
==8475== Use --history-level=approx or =none to gain increased speed, at
==8475== the cost of reduced accuracy of conflicting-access information
==8475== For lists of detected and suppressed errors, rerun with: -s
==8475== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
Segmentation fault (core dumped)



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
