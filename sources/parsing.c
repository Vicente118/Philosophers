#include "../includes/philo.h"

int check_number(char **argv)
{
    int     i;
    int     j;
    char    *trim;

    i = 1;
    while (argv[i])
    {
        trim = ft_strtrim(argv[i], " ");
        j = 0;
        while (trim[j])
        {
            if (trim[j] < '0' || trim[j] > '9')
            {
                write(2, "Wrong format, please enter positive number\n", 44);
                return (0);
            }
            j++;
        }
        free(trim);
        i++;
    }
    return (1);
}

int check_input(char **argv)
{
    if (!check_number(argv))
        return (0);
    if (ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
    {
        write(2, "Wrong format, enter a valid time higher than 0\n", 48);
        return (0);
    }
    if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 1)
    {
        write(2, "Wrong number of philosophers\n", 30);
        return (0);
    }
    return (1);
}

int init_all(t_data *data)
{
    if (!init_data(data))
        return (0);
    init_philo(data);
    return (1);
}