#include "../include/philo.h"

size_t	ft_tab_size(char **s)
{
	int	n;

	n = 0;
	while (1)
	{
		if (s[n] == NULL)
		{
			return (n);
		}
		n++;
	}
}

/*

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}
*/
