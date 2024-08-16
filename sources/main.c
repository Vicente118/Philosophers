#include "../includes/philo.h"

void	one_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(data->time_to_die);
	printf("%lld 1 died\n", data->time_to_die);
}

int	check_arg(int argc)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong number of arguments\n", 27);
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;

	data.argc = argc;
	data.argv = argv;
	if (!check_arg(argc))
		return (1);
	if (!check_input(argv))
		return (1);
	if (!init_all(&data))
		return (1);
	if (data.number_philo == 1)
	{
		one_philo(&data);
		return (destroy_mutex_and_free(&data), 0);
	}
	if (!start_simulation(&data))
		return (destroy_mutex_and_free(&data), 1);
	return (destroy_mutex_and_free(&data), 0);
}
