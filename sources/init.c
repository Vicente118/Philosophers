#include "../includes/philo.h"

long long get_time_ms(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int init_data(t_data *data)
{
    int i;

    data->number_philo = (int)ft_atoi(data->argv[1]);
    data->time_to_die = (long long)ft_atoi(data->argv[2]);
    data->time_to_eat = (long long)ft_atoi(data->argv[3]);
    data->time_to_sleep = (long long)ft_atoi(data->argv[4]);
    data->is_dead = 0;
    if (data->argc == 6)
        data->meals_to_eat = (int)ft_atoi(data->argv[5]);
    else
        data->meals_to_eat = -1;
    data->philos = malloc(sizeof(t_philo) * data->number_philo);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philo);
    if (!data->philos || !data->forks)
        return (write(2, "Error: memory allocation\n", 26), 0);
    i = -1;
    while (++i < data->number_philo)
    {
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (write(2, "Error mutex init\n", 18), 0);
    }
    if (pthread_mutex_init(&data->print_lock, NULL))
        return (write(2, "Error mutex init\n", 18), 0);
    data->start_time = get_time_ms();
    return (1);
}

void init_philo(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_philo)
    {
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = i;
        data->philos[i].right_fork = (i + 1) % data->number_philo;
        data->philos[i].last_meal_time = data->start_time;
        data->philos[i].times_eaten = 0;
        data->philos[i].is_eating = 0;
        data->philos[i].last_meal = 0;
        data->philos[i].data = data;
        i++;
    }
}