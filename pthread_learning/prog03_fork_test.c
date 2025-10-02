#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>

#include <stdio.h>

int	main(void)
{
	pid_t	pid;
	
	printf("Hello!\n");
	printf("My pid=%jd\n", (intmax_t)getpid());
	printf("My parent's pid=%jd\n", (intmax_t)getppid());
	sleep(5);
	pid = fork();
	printf("Doing some work\n");
	sleep(5);
	printf("Bye!");
	return (0);
}
