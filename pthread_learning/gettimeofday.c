#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/time.h>

int	main(void)
{
	struct timeval	tv;
	int				ret;

	ret = gettimeofday(&tv, NULL);
	if (ret)
		perror("gettimeofday");
	else
		printf("seconds=%ld microseconds=%ld\n",
			(long)tv.tv_sec, (long)tv.tv_usec);
	return (EXIT_SUCCESS);
}
