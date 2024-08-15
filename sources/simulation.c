#include "../includes/philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *data = philo->data;

    while (!data->is_dead) 
    {
        if (data->meals_to_eat != -1 && philo->times_eaten >= data->meals_to_eat)
        {
            philo->last_meal = 1; 
            break;
        }
        // Penser
        think(data, philo);
        // Prendre les fourchettes
        if (philo->id % 2 == 0)
            usleep(100);
        take_fork(data, philo, &data->forks[philo->right_fork], &data->forks[philo->left_fork]);
        // Manger
        eat(data, philo);
        // Relâcher les fourchettes
        release_fork(data, philo);
        // Dormir
        philo_sleep(data, philo);
        // Vérifier si le nombre minimal de repas a été atteint
    }
    return (NULL);
}

void    *check_death(void *arg)
{
    int i;
    t_data  *data;

    data = (t_data *) arg;
    while (data->is_dead == 0)
    {
        i = 0;
        if (check_last_meal(data))
            return (NULL);
        while (i < data->number_philo)
        {
            if (get_time_ms() - data->philos[i].last_meal_time > data->time_to_die)
            {
                if (data->philos[i].is_eating == 1)
                    break ;
                pthread_mutex_lock(&data->print_lock);
                printf("%lld %d died\n", get_time_ms() - data->start_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print_lock);
                data->is_dead = 1;
                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}

int check_last_meal(t_data *data)
{
    int i;

    i = 0;
    if (data->meals_to_eat == -1)
        return (0);
    while (i < data->number_philo)
    {
        if (data->philos[i].last_meal != 1)
            return (0);
        i++;
    }
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