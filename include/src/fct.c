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
	arg->start_time = get_time_in_ms();
	arg->stock = INITIAL_STOCK;
	arg->index = 0;
	pthread_mutex_init(&arg->mutex_stock, 0);
	arg->chair = malloc(sizeof(t_thread_data) * arg->nbr_philo);
	if(arg->chair == NULL)
		exit(EXIT_FAILURE);///CHANGE THIS
	arg->nbr_philo = ft_atoi(s[1]);
	arg->time_to_die = ft_atoi(s[2]);
	arg->stop = 2;
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
