#include "../philo.h"


void init_error( int error_return)
{
    if(!error_return)
        return;
    if(error_return == ENOMEM)
        exit_on_error("Insufficient memory exists to initialize the mutex.");
    if(error_return == EAGAIN)
        exit_on_error("The system lacked the necessary resources \
            (other than memory) to initialize another mutex.");
    if(error_return == EPERM)
        exit_on_error("The caller does not have the privilege\
            to perform the operation.");
}
void lock_error( int error_return)
{
    if(!error_return)
        return;
    if(error_return == EDEADLK)
        exit_on_error("The current thread already owns the mutex.");
    if(error_return == EAGAIN)
        exit_on_error("The mutex could not be acquired because the maximum \
         number of recursive locks for mutex has been exceeded.");
    if(error_return == EOWNERDEAD)
        exit_on_error("The last owner of this mutex terminated\
            while holding the mutex.");
    if(error_return == ENOTRECOVERABLE)
        exit_on_error("The mutex you are trying to\
         acquire was protecting state left irrecoverable by\
         the mutexs previous owner.");
    if(error_return == ENOMEM)
        exit_on_error("The limit on the number of simultaneously\
             held mutexes has been exceeded.");
}

void destroy_error( int error_return)
{
    if(!error_return)
        return;
    if(error_return == EBUSY)
        exit_on_error("Attempt to destroy the object referenced by\
            mutex while it was locked");
    if(error_return == EINVAL)
        exit_on_error("The value specified by mutex is not valid.");
 }

void unlock_error( int error_return)
{
    if(!error_return)
        return;
    if(error_return == EPERM)
        exit_on_error("The current thread does not own the mutex.");

}

 void safe_mutex(pthread_mutex_t *mtx, t_mtx_option option){
    if (option == INIT)
        init_error(pthread_mutex_init(mtx, NULL));
    if (option == LOCK)
        lock_error( pthread_mutex_lock(mtx));
    if (option == UNLOCK)
        unlock_error( pthread_mutex_unlock(mtx));
    if (option == DESTROY)
        destroy_error( pthread_mutex_destroy(mtx));
}