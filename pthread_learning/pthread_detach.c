#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>

void	*start_routine(void *arg)
{
	(void)arg;
	printf("start_routine() thread has started its work\n");
	sleep(2);
	printf("start_routine() thread has terminated\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, start_routine, NULL) != 0)
	{
		perror("pthread_create");
		return (EXIT_FAILURE);
	}
	if (pthread_detach(thread) != 0)
	{
		perror("pthread_detach");
		return (EXIT_FAILURE);
	}
	printf("The main thread does not wait through join\n");
	sleep(3);
	printf("The main thread terminates the program\n");
	return (EXIT_SUCCESS);
}
