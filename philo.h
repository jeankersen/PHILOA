#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>


#define INITIAL_STOCK   20
#define NB_CLIENTS      5






int get_random (int max);
void * fn_store (void * p_data);

#endif
