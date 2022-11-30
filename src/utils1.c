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

