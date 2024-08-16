#include "../includes/philo.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *data = philo->data;

    while (1) 
    {
        // Vérifier si un philosophe est mort
        pthread_mutex_lock(&data->dead_mutex);
        if (data->is_dead)
        {
            pthread_mutex_unlock(&data->dead_mutex);
            break;
        }
        pthread_mutex_unlock(&data->dead_mutex);

        // Vérifier si le philosophe a fini ses repas
        pthread_mutex_lock(&data->eat_mutex);
        if (data->meals_to_eat != -1 && philo->times_eaten >= data->meals_to_eat)
        {
            pthread_mutex_unlock(&data->eat_mutex);
            break;
        }
        pthread_mutex_unlock(&data->eat_mutex);

        // Penser
        think(data, philo);

        // Vérification avant de prendre les fourchettes
        pthread_mutex_lock(&data->eat_mutex);
        if (get_time_ms() - philo->last_meal_time + data->time_to_eat > data->time_to_die)
        {
            pthread_mutex_unlock(&data->eat_mutex);
            break;
        }
        pthread_mutex_unlock(&data->eat_mutex);

        // Prendre les fourchettes
        if (philo->id % 2 == 0)
            usleep(100); // Éviter les deadlocks en retardant les philosophes pairs
        take_fork(data, philo, &data->forks[philo->right_fork], &data->forks[philo->left_fork]);

        // Manger
        eat(data, philo);

        // Relâcher les fourchettes
        release_fork(data, philo);

        // Dormir
        philo_sleep(data, philo);
    }

    return NULL;
}

void *check_death(void *arg)
{
    t_data *data = (t_data *) arg;
    int i;

    while (1) 
    {
        pthread_mutex_lock(&data->dead_mutex);
        if (data->is_dead)
        {
            pthread_mutex_unlock(&data->dead_mutex);
            break;
        }
        pthread_mutex_unlock(&data->dead_mutex);

        i = 0;
        while (i < data->number_philo)
        {
            pthread_mutex_lock(&data->eat_mutex);
            if (get_time_ms() - data->philos[i].last_meal_time > data->time_to_die)
            {
                pthread_mutex_unlock(&data->eat_mutex);

                pthread_mutex_lock(&data->print_lock);
                printf("%lld %d died\n", get_time_ms() - data->start_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print_lock);

                pthread_mutex_lock(&data->dead_mutex);
                data->is_dead = 1;
                pthread_mutex_unlock(&data->dead_mutex);

                return NULL;
            }
            pthread_mutex_unlock(&data->eat_mutex);
            i++;
        }
        if (check_last_meal(data))
        {
            pthread_mutex_lock(&data->dead_mutex);
            data->is_dead = 1;
            pthread_mutex_unlock(&data->dead_mutex);
            return NULL;
        }
        usleep(100);  // Réduire le délai pour vérifier plus fréquemment
    }

    return NULL;
}

int check_last_meal(t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_lock(&data->eat_mutex);
    if (data->meals_to_eat == -1)
    {
        pthread_mutex_unlock(&data->eat_mutex);
        return (0);
    }
    while (i < data->number_philo)
    {
        if (data->philos[i].last_meal != 1)
        {
            pthread_mutex_unlock(&data->eat_mutex);
            return (0);
        }
        i++;
    }
    pthread_mutex_unlock(&data->eat_mutex);
    return (1);
}

int start_simulation(t_data *data)
{
    pthread_t   death_checker;
    int         i;

    i = 0;
    while (i < data->number_philo)
    {
        if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]))
            return (write(2, "Error with thread creation\n", 28), 0);
        i++;
    }
    if (pthread_create(&death_checker, NULL, &check_death, data))
        return (write(2, "Error with thread creation\n", 28), 0);
    i = 0;
    while (i < data->number_philo)
    {
        if (pthread_join(data->philos[i].thread, NULL))
            return (write(2, "Error with phtread_join\n", 25), 0);
        i++;
    }
    if (pthread_join(death_checker, NULL))
            return (write(2, "Error with phtread_join\n", 25), 0);
    return (1);
}