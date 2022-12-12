#include "../include/philo.h"

/* thread function */


void *ft_philo(void *arg)
{
	t_data *data = (t_data *)arg;
	long nb = data->index;
	while (data->stop >1)
	{
		int val = get_random(6);
		/*Protected zone by mutex lock*/
		long time = get_time_in_ms();
		ft_usleep(1000);
		if(time - data->start_time > data->time_to_die)
		{
			check_death(arg, nb, time);
		}
		else
		{
			pthread_mutex_lock(&data->mutex_stock);
			data->stock = data->stock - val;
			printf("[%ld] philo %ld prend %d, il reste %d\n", time - data->start_time, nb+1, val, data->stock);
			/*End of the protected zone*/
			pthread_mutex_unlock(&data->mutex_stock);
		}
		//return NULL;
	}
	return NULL;
}


int create_thread(t_data *data)
{

	int rc;
		while(data->index < data->nbr_philo)
		{
			 /*Create  thread data struct array */
    		rc = pthread_create(&data->chair[data->index].philo, NULL, ft_philo, (void *) data);
			if(rc)
			{
      			printf("error: pthread_create, rc: %d\n", rc);
      			exit(0);
    		}
			data->index++;
  		}

  	data->index = 0;


  	/* Block until all threads complete */
  	while(data->index < data->nbr_philo)
  	{
		if(pthread_join(data->chair[data->index].philo, NULL) != 0)
		{
			data->index = data->nbr_philo;
			return 0;
		}
		data->index++;
  	}

	return 0;
}


int main(int argc, char **argv)
{
	t_data arg;

	if(argc == 3)
	{
		init_arg(&arg, argv);

		create_thread(&arg);

	}
	else{
	printf("bad arg\n");

	}

	free_all(&arg);
	return EXIT_SUCCESS;
}


//on a le temps a verifier
//freee
