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
#define NB_PHILO      5


typedef struct s_data
{
   int stock;
   long id_t;

   time_t   start_time;

   pthread_t thread_manager;
   pthread_t thread_philo[NB_PHILO];

   pthread_mutex_t mutex_stock;


   pthread_cond_t cond_stock;
   pthread_cond_t cond_philo;
} t_data;


void init_arg(t_data *data);
time_t	get_time_in_ms(void);
int get_random (int max);

#endif
