#include "../includes/philo.h"

static int	skip(char *str)
{
	size_t	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long int	res;
	long int	buff;
	int			signe;

	res = 0;
	buff = 0;
	signe = 1;
	str += skip((char *)str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (buff > res && signe > 0)
			return (-1);
		else if (buff > res && signe < 0)
			return (0);
		str++;
		buff = res;
	}
	return (res * signe);
}