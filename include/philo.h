#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#define psleep(sec) sleep ((sec))
#define INITIAL_STOCK   20
#define NB_CLIENTS      5



// structure avec les threads
typedef struct
{
   int stock;

   pthread_t thread_store;
   pthread_t thread_clients [NB_CLIENTS];

   pthread_mutex_t mutex_stock;
}
store_t;



int get_random (int max);
void * fn_store (void * p_data);

#endif
