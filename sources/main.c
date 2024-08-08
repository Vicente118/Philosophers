#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void	*make_coffee(void *data)
{
	printf("Coffee is almost ready...\n");
	sleep(1);
	printf("Coffee is ready !\n");
	return (NULL);
}

int main(void)
{
	pthread_t coffee[200];
	int	i = 0;

	while (i < 200)
	{
		pthread_create(&coffee[i], NULL, &make_coffee, NULL);
		i++;
	}
	i = 0;
	while (i < 200)
	{
		pthread_join(coffee[i], NULL);
		i++;
	}
	return (0);
}