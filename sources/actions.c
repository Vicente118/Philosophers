#include "../includes/philo.h"

void	think(t_data *data, t_philo *philo)
{	
	if (data->is_dead == 0)
	{
   		printf("%lld %d is thinking\n", get_time_ms() - data->start_time, philo->id);
	}
}

void eat(t_data *data, t_philo *philo)
{
    philo->is_eating = 1;
    if (!data->is_dead)
	{
        printf("%lld %d is eating\n", get_time_ms() - data->start_time, philo->id);
	}	
    philo->is_eating = 0;
    philo->last_meal_time = get_time_ms();
    philo->times_eaten++;
    usleep(data->time_to_eat * 1000);  // Convertir en microsecondes

}


void	philo_sleep(t_data *data, t_philo *philo)
{
	if (data->is_dead == 0)
	{
		printf("%lld %d is sleeping\n", get_time_ms() - data->start_time, philo->id);
	}
	usleep(data->time_to_sleep * 1000);
}

void take_fork(t_data *data, t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
    pthread_mutex_lock(fork1);
    if (!data->is_dead)
	{
        printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
	}
    pthread_mutex_lock(fork2);
    if (!data->is_dead)
	{
        printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
	}
}


void	release_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
    pthread_mutex_unlock(&data->forks[philo->right_fork]);
}