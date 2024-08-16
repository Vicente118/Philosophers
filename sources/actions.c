#include "../includes/philo.h"

void	think(t_data *data, t_philo *philo)
{	
	pthread_mutex_lock(&data->dead_mutex);
	if (data->is_dead == 0)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_lock(&data->print_lock);
   		printf("%lld %d is thinking\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_lock);
	}
	else
		pthread_mutex_unlock(&data->dead_mutex);
}

void eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->eat_mutex);
    philo->is_eating = 1;
	pthread_mutex_unlock(&data->eat_mutex);
	pthread_mutex_lock(&data->dead_mutex);
    if (!data->is_dead)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_lock(&data->print_lock);
        printf("%lld %d is eating\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_lock);
	}
	else
		pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_lock(&data->eat_mutex);
    philo->is_eating = 0;
    philo->last_meal_time = get_time_ms();
    philo->times_eaten++;
	pthread_mutex_unlock(&data->eat_mutex);
    usleep(data->time_to_eat * 1000);  // Convertir en microsecondes

}


void	philo_sleep(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->is_dead == 0)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_lock(&data->print_lock);
		printf("%lld %d is sleeping\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_lock);
	}
	else
		pthread_mutex_unlock(&data->dead_mutex);
	usleep(data->time_to_sleep * 1000);
}

void take_fork(t_data *data, t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
    // Toujours verrouiller les fourchettes dans le même ordre
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(fork1);
        pthread_mutex_lock(&data->dead_mutex);
        if (!data->is_dead)
        {
            pthread_mutex_unlock(&data->dead_mutex);
            pthread_mutex_lock(&data->print_lock);
            printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print_lock);
        }
        else
        {
            pthread_mutex_unlock(&data->dead_mutex);
            pthread_mutex_unlock(fork1);  // Libère la fourchette si mort
            return;
        }

        pthread_mutex_lock(fork2);
        pthread_mutex_lock(&data->dead_mutex);
        if (!data->is_dead)
        {
            pthread_mutex_unlock(&data->dead_mutex);
            pthread_mutex_lock(&data->print_lock);
            printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print_lock);
        }
        else
        {
            pthread_mutex_unlock(&data->dead_mutex);
            pthread_mutex_unlock(fork2);  // Libère la fourchette si mort
            pthread_mutex_unlock(fork1);  // Libère la première fourchette aussi
            return;
        }
    }
    else
    {
        pthread_mutex_lock(fork2);
        pthread_mutex_lock(&data->dead_mutex);
        if (!data->is_dead)
        {
            pthread_mutex_unlock(&data->dead_mutex);
            pthread_mutex_lock(&data->print_lock);
            printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print_lock);
        }
        else
        {
            pthread_mutex_unlock(&data->dead_mutex);
            pthread_mutex_unlock(fork2);  // Libère la fourchette si mort
            return;
        }

        pthread_mutex_lock(fork1);
        pthread_mutex_lock(&data->dead_mutex);
        if (!data->is_dead)
        {
            pthread_mutex_unlock(&data->dead_mutex);
            pthread_mutex_lock(&data->print_lock);
            printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print_lock);
        }
        else
        {
            pthread_mutex_unlock(&data->dead_mutex);
            pthread_mutex_unlock(fork1);  // Libère la fourchette si mort
            pthread_mutex_unlock(fork2);  // Libère la deuxième fourchette aussi
            return;
        }
    }
}



void	release_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
    pthread_mutex_unlock(&data->forks[philo->right_fork]);
}