#include "../include/philo.h"

/* thread function */


void *ft_philo(void *arg)
{
	t_data *data = (t_data *)arg;
	long nb = data->index;
	while (1)
	{
		int val = get_random(6);
		/*Protected zone by mutex lock*/
		usleep(2000000);
		pthread_mutex_lock(&data->mutex_stock);
		if(val > data->stock)
		{
			data->stock = INITIAL_STOCK;
			printf("Remplisaage du stock de %d articles\n", data->stock);
		}
		time_t time = get_time_in_ms();
		data->stock = data->stock - val;
		printf("[%ld] philo %ld prend %d, il reste %d\n", time - data->start_time, nb, val, data->stock);
		/*End of the protected zone*/
		pthread_mutex_unlock(&data->mutex_stock);
	}
	return NULL;
}


void create_thread(t_data *data)
{

	int rc;

		while(data->index < NUM_THREADS)
		{
			 /*Create  thread data struct array */
    		rc = pthread_create(&data->chair[data->index].philo[data->index], NULL, ft_philo, (void *) data);
			if(rc)
			{
      			printf("error: pthread_create, rc: %d\n", rc);
      			exit(0);
    		}
			data->index++;
  		}

  	data->index = 0;


  	/* Block until all threads complete */
  	while(data->index < NUM_THREADS)
  	{
    	pthread_join(data->chair[data->index].philo[data->index], NULL);
		data->index++;
  	}

}


int main()
{
	t_data arg;

	init_arg(&arg);

	create_thread(&arg);

	return EXIT_SUCCESS;
}


///verifier lheure, ensuite on prend le arguments...
