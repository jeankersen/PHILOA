#ifndef PHILO_H
# define PHILO_H

#define NUM_THREADS 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

#define INITIAL_STOCK   20

typedef struct s_thread_data {
  int tid;
  double stuff;
  pthread_t philo[NUM_THREADS];
} t_thread_data;

typedef struct s_data
{
	time_t start_time;
	long index;
	int stock;
	t_thread_data chair[NUM_THREADS];
	pthread_mutex_t mutex_stock;
} t_data;

/*Initiate all variables we need*/
void init_arg(t_data *arg);

/*Get time in ms*/
time_t	get_time_in_ms(void);

/*Get random number*/
int get_random (int max);



#endif
