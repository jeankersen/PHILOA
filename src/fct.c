#include "../include/philo.h"
/*Return time in miliseconds */

long long	get_time_in_ms(void)
{
	struct timeval	tv;
	/*
	struct    timeval  {
  time_t        tv_sec ;   //used for seconds
  suseconds_t       tv_usec ;   //used for microseconds
	}
	*/

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


int	ft_atoi(const char *str)
{
	int		negative;
	long	nb;

	negative = 1;
	nb = 0;
	while ((*str >= '\t' && *str <= '\r') || (*str == ' '))
		str++;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + *str - 48;
		str++;
		if (nb * negative > 2147483647)
			return (-1);
		if (nb * negative < -2147483648)
			return (0);
	}
	return (nb * negative);
}

void init_arg(t_data *arg, char **s)
{
	int i = 0;
	arg->start_time = get_time_in_ms();

	arg->index = 0;
	pthread_mutex_init(&arg->mutex_stop, 0);
	pthread_mutex_init(&arg->mutex_dead, 0);
	pthread_mutex_init(&arg->mutex_print, 0);
	arg->chair = malloc(sizeof(t_thread_data) * arg->nbr_philo);
	arg->nbr_philo = ft_atoi(s[1]);
	arg->time_to_die = ft_atoi(s[2]);
	arg->time_to_eat = ft_atoi(s[3]);
	arg->time_to_sleep = ft_atoi(s[4]);
	arg->chair = malloc(sizeof(t_thread_data) * arg->nbr_philo);

	arg->stop = 0;
	while (i < arg->nbr_philo)
	{
		pthread_mutex_init(&arg->chair[i].mutex_fork_l, 0);
		arg->chair[i].fork = 1;
		arg->chair[i].last_time_eat = arg->start_time;
		arg->chair[i].fork = 1;
		i++;
	}

}


void free_all(t_data *arg)
{
	int i = 0;
	while (i < arg->nbr_philo)
	{
		pthread_mutex_destroy(&arg->chair[i].mutex_fork_l);
		i++;
	}
	pthread_mutex_destroy(&arg->mutex_dead);
	pthread_mutex_destroy(&arg->mutex_print);
	pthread_mutex_destroy(&arg->mutex_stop);
	free(arg->chair);

}


 int get_random (int max)
{
   double val;

   val = (double) max * rand ();
   val = val / (RAND_MAX + 1.0);

   return ((int) val);
}


void	ft_usleep(int ms)
{
	long int	time;

	time = get_time_in_ms();
	while (get_time_in_ms() - time < ms)
		usleep(ms / 10);
}


int	is_dead(t_data *data, int nb)
{
	pthread_mutex_lock(&data->mutex_dead);
	if(nb)
		data->stop = 1;
	if (data->stop)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_dead);
	return (0);
}


/*

void take_fork(t_data *data, long nb)
{
	//long nb = data->index;
	long time = get_time_in_ms();
	pthread_mutex_lock(&data->chair[nb].mutex_fork_l);
	time = get_time_in_ms();
		//data->stock = data->stock - val;
		pthread_mutex_lock(&data->mutex_print);
	printf("[%ld] philo %ld has taken a fork\n", time - data->start_time, nb+1);
	pthread_mutex_unlock(&data->mutex_print);
	//pthread_mutex_unlock(&data->chair[nb].mutex_fork_l);


	if(nb < data->nbr_philo-2)
	{
		time = get_time_in_ms();
		pthread_mutex_lock(&data->chair[nb+1].mutex_fork_l);
		pthread_mutex_lock(&data->mutex_print);
		printf("[%ld] philo %ld has taken a fork\n", time - data->start_time, nb+1);
		pthread_mutex_unlock(&data->mutex_print);
	}
	else if(nb == data->nbr_philo -1)
	{
		time = get_time_in_ms();
		pthread_mutex_lock(&data->chair[0].mutex_fork_l);
		pthread_mutex_lock(&data->mutex_print);
		printf("[%ld] philo %ld has taken a fork\n", time - data->start_time, nb+1);
		pthread_mutex_unlock(&data->mutex_print);
	}
}

void eating(t_data *data, long nb)
{
	long time = get_time_in_ms();
	data->chair[nb].last_time_eat = get_time_in_ms();
	pthread_mutex_lock(&data->mutex_print);
	printf("[%ld] philo %ld is eating\n", time - data->start_time, nb+1);
	pthread_mutex_unlock(&data->mutex_print);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->chair[nb].mutex_fork_l);
	if(nb < data->nbr_philo-2)
	{
		pthread_mutex_unlock(&data->chair[nb+1].mutex_fork_l);
	}
	else if(nb == data->nbr_philo -1)
	{
		pthread_mutex_unlock(&data->chair[0].mutex_fork_l);
	}
	time = get_time_in_ms();
	pthread_mutex_lock(&data->mutex_print);
	printf("[%ld] philo %ld is sleeping\n", time - data->start_time, nb+1);
	pthread_mutex_unlock(&data->mutex_print);
	ft_usleep(data->time_to_sleep);
	time = get_time_in_ms();
	pthread_mutex_lock(&data->mutex_print);
	printf("[%ld] philo %ld is thinking\n", time - data->start_time, nb+1);
	pthread_mutex_unlock(&data->mutex_print);
}


void *check_death(t_data *data, long nb, long time)
{
	pthread_mutex_lock(&data->mutex_stock);
	if(data->stop > 1)
		printf("[%ld] philo %ld die\n", time - data->start_time, nb+1);
	data->stop = 0;
	pthread_mutex_unlock(&data->mutex_stock);
	return NULL;
}
 */
