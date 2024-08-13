#include "../includes/philo.h"

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
	start_simulation(&data);
	return (0);
}