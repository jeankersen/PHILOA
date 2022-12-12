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
  pthread_t philo;
} t_thread_data;

typedef struct s_data
{
	long int start_time;
	int	time_to_die;
	int nbr_philo;
	long index;
	int stock;
	int stop;
	t_thread_data *chair;
	pthread_mutex_t mutex_stock;
} t_data;

/*Initiate all variables we need*/
void init_arg(t_data *arg, char **s);

/*Get time in ms*/
long long	get_time_in_ms(void);

/*Get random number*/
int get_random (int max);

void	ft_usleep(int ms);

void free_all(t_data *arg);

void *check_death(t_data *data, long nb, long time);

#endif
