#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


#define INITIAL_STOCK   20
#define NB_CLIENTS      5


typedef struct s_store
{
   int stock;
   long id_t;

   pthread_t thread_store;
   pthread_t thread_clients[NB_CLIENTS];

   pthread_mutex_t mutex_stock;


   pthread_cond_t cond_stock;
   pthread_cond_t cond_clients;
} t_store;




int get_random (int max);

#endif
