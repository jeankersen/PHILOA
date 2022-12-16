#include "../include/philo.h"

/* thread function */
void	*check_death(void  *arg)
{
	t_data *data = (t_data *)arg;
	long nb = data->index;
	//ft_usleep(1000);

	pthread_mutex_lock(&data->chair[nb].mutex_fork_l);
	pthread_mutex_lock(&data->mutex_stop);//2-zone proterer de stop
	if (!is_dead(data, 0) && data->chair[nb].fork < 1) // 3-condition pour la mort et autre-
	{

		pthread_mutex_unlock(&data->chair[nb].mutex_fork_l);
		pthread_mutex_unlock(&data->mutex_stop);
		pthread_mutex_lock(&data->mutex_print);
		long time = get_time_in_ms();

		if(!is_dead(data, 0) && !data->stop)
			printf("[%ld] philo %ld               die[%d]\n", time - data->start_time, nb+1, data->chair[nb].fork);
		pthread_mutex_unlock(&data->mutex_print);

		is_dead(data, 1);

	}

	pthread_mutex_unlock(&data->chair[nb].mutex_fork_l);

	pthread_mutex_unlock(&data->mutex_stop);

	return (NULL);
}


void *ft_philo(void *arg)
{
	t_data *data = (t_data *)arg;
	long nb = data->index;
	pthread_t	t;

	while (!is_dead(data, 0))
	{

		pthread_create(&t, NULL, check_death, arg);
		/*Protected zone by mutex lock*/

		pthread_mutex_lock(&data->chair[nb].mutex_fork_l);
		long time = get_time_in_ms();
		pthread_mutex_lock(&data->mutex_print);
		ft_usleep(10);
		if(data->chair[nb].fork >= 1 && !is_dead(data, 0))
		{

			printf("[%ld] philo %ld has taken a fork[%d]\n", time - data->start_time, nb+1, data->chair[nb].fork);
			data->chair[nb].fork--;

		}

		pthread_mutex_unlock(&data->mutex_print);
		pthread_mutex_unlock(&data->chair[nb].mutex_fork_l);
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
		if(rc != 0)
		{
			printf("error: pthread_create, rc: %d\n", rc);
			return 0;
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

	if(argc == 5)
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


// faire mourrir un phiolo
