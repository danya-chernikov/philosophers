#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define ITERATIONS	10000

int	g_counter = 0;
pthread_mutex_t	g_mutex;

void	*start_routine(void *arg)
{
	int	i;

	(void)arg;
	i = 0;
	while (i < ITERATIONS)
	{
		pthread_mutex_lock(&g_mutex);
		++g_counter;
		pthread_mutex_unlock(&g_mutex);
		++i;
	}
	return (NULL);
}

/* We should not call pthread_mutex_destroy()
 * while the mutex is still in use or locked */
int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_mutex_init(&g_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init");
		return (EXIT_FAILURE);
	}
	if (pthread_create(&t1, NULL, start_routine, NULL) != 0)
	{
		perror("pthread_create");
		pthread_mutex_destroy(&g_mutex);
		return (EXIT_FAILURE);
	}
	if (pthread_create(&t2, NULL, start_routine, NULL) != 0)
	{
		perror("pthread_create");
		pthread_join(t1, NULL);
		pthread_mutex_destroy(&g_mutex);
		return (EXIT_FAILURE);
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("g_counter = %d\n", g_counter);
	if (pthread_mutex_destroy(&g_mutex) != 0)
	{
		perror("pthread_mutex_destroy");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
