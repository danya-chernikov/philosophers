#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	/* the child ... */
	if (!pid)
	{
		const char	*args[] = { "lsblk", NULL };
		int	ret;

		printf("Hi! I'm %jd!\n", (intmax_t)getpid());
		ret = execv("/bin/lsblk", (char *const *)args);
		if (ret == -1)
		{
			perror("execv");
			exit(EXIT_FAILURE);
		}
	}
	printf("Hi! I'm %jd! Let's continue doing something :D\n", (intmax_t)getpid());
	sleep(5);
	return (0);
}
