#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>

#include "logger.h"




#define  MAX_COUNT_LOOP_ITERATIONS  (1000000)


Logger_r rlog;

pthread_t test_threads[2];



void perror_exit(const char *error_message)
{
    printf("error: %s\n", error_message);
    exit(EXIT_FAILURE);
}



void* test_atomic_thread1(void *thread_arg)
{
    unsigned int i;

    for(i = 0; i < MAX_COUNT_LOOP_ITERATIONS; i++)
    {
        rlog << Logger_r::lm_lock;
        rlog << Logger_r::ll_fatal << "-----------------" << 1 << '#' << 1.111111 << std::endl;
        rlog << Logger_r::lm_unlock;
    }


    return NULL;
}



void* test_atomic_thread2(void *thread_arg)
{
    unsigned int i;

    for(i = 0; i < MAX_COUNT_LOOP_ITERATIONS; i++)
    {
        LogLocker lock(rlog);
        rlog << Logger_r::ll_error << "=================" << 2 << '#' << 2.222222 << std::endl;
    }


    return NULL;
}



void start_test_threads(void)
{

    rlog.open("test_r.log");

    if( !rlog.is_open() )
        perror_exit("Cant open test_r.log");

    rlog.set_max_index(3);
    rlog.set_max_size(10<<20);


    if(pthread_create(&test_threads[0], NULL, test_atomic_thread1, NULL) != 0)
      perror_exit("Cant create thread1");


    if(pthread_create(&test_threads[1], NULL, test_atomic_thread2, NULL) != 0)
      perror_exit("Cant create thread2");


    if(pthread_join(test_threads[0], NULL) != 0)
          perror_exit("Cant join thread1");


    if(pthread_join(test_threads[1], NULL) != 0)
          perror_exit("Cant join thread2");

}



int main()
{
    start_test_threads();

    return EXIT_SUCCESS; // good job
}
