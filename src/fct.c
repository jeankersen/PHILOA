#include "../include/philo.h"


/* Fonction pour tirer un nombre au sort entre 0 et max. */

int get_random (int max)
{
   double val;

   val = (double) max * rand();
   val = val / (RAND_MAX + 1.0);

   return ((int) val);
}


time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


void init_arg(t_data *data)
{
   data->stock = INITIAL_STOCK;

   data->id_t = 1;

   data->start_time = get_time_in_ms();

   pthread_mutex_init(&data->mutex_stock, 0);
	pthread_cond_init(&data->cond_stock, 0);
	pthread_cond_init(&data->cond_philo, 0);
}
