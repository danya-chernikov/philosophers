#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <unistd.h>
#include <pthread.h>

#define N	100

void	*start_routine(void *thread_num);

int	main(void)
{
	pthread_t	tid;
	int			ret;
	int			thread_cnt;

	thread_cnt = 0;
	ret = pthread_create(&tid, NULL, start_routine, &thread_cnt);
	if (ret)
	{
		errno = ret;
		perror("pthread_create");
		return (EXIT_FAILURE);
	}
	ret = pthread_join(tid, NULL);
	if (ret)
	{
		perror("pthread_join");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*start_routine(void *thread_num)
{
	++(*(int *)thread_num);
	for (int i = 0; i < N; ++i)
	{
		printf("Hi! I'm thread number %i. I'm saying %i\n",
			*(int *)thread_num, i);
		usleep(50000);
	}
	return (NULL);
}
