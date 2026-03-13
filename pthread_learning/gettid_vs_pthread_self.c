#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define CL_RESET	"\033[0m"
#define CL_GREEN	"\033[32m"
#define CL_BLUE		"\033[34m"

#define N			100

void	*start_routine1(void *thread_num);
void	*start_routine2(void *thread_num);

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	int			ret;
	int			thread_cnt;

	thread_cnt = 0;
	ret = pthread_create(&tid1, NULL, start_routine1, &thread_cnt);
	if (ret)
	{
		errno = ret;
		perror("pthread_create");
		return (EXIT_FAILURE);
	}
	ret = pthread_create(&tid2, NULL, start_routine2, &thread_cnt);
	if (ret)
	{
		errno = ret;
		perror("pthread_create");
		return (EXIT_FAILURE);
	}
	ret = pthread_join(tid1, NULL);
	if (ret)
	{
		perror("pthread_join");
		return (EXIT_FAILURE);
	}
	ret = pthread_join(tid2, NULL);
	if (ret)
	{
		perror("pthread_join");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*start_routine1(void *thread_num)
{
	++(*(int *)thread_num);
	for (int i = 0; i < N; ++i)
	{
		printf("%sHi! I'm thread number %i. "
			"getpid()=%jd; gettid()=%jd; pthread_self()=%i : I'm saying %i%s\n",
			CL_BLUE,
			*(int *)thread_num,
			(intmax_t)getpid(),
			(intmax_t)gettid(),
			(int)pthread_self(),
			i,
			CL_RESET);
		usleep(50000);
	}
	pthread_exit(0);
	return (NULL);
}

void	*start_routine2(void *thread_num)
{
	++(*(int *)thread_num);
	for (int i = 0; i < N; ++i)
	{
		printf("%sHi! I'm thread number %i. "
			"getpid()=%jd; gettid()=%jd; pthread_self()=%i : I'm saying %i%s\n",
			CL_GREEN,
			*(int *)thread_num,
			(intmax_t)getpid(),
			(intmax_t)gettid(),
			(int)pthread_self(),
			i,
			CL_RESET);
		usleep(50000);
	}
	pthread_exit(0);
	return (NULL);
}
