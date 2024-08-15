#include "../includes/philo.h"

void	destroy_mutex_and_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->lock);
	free(data->philos);
	free(data->forks);
}
