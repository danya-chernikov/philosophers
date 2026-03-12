#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>

#include <stdio.h>

int	main(void)
{
	pid_t	pid;
	
	printf("%jd is saying: Hello!\n", (intmax_t)getpid());
	printf("%jd is saying: My pid=%jd\n", (intmax_t)getpid(), (intmax_t)getpid());
	printf("%jd is saying: My parent's pid=%jd\n", (intmax_t)getpid(), (intmax_t)getppid());
	printf("%jd is saying: sleeping...\n", (intmax_t)getpid());
	sleep(5);
	printf("%jd is saying: First fork()!\n\n", (intmax_t)getpid());
	pid = fork();

	printf("%jd is saying: Hello!\n", (intmax_t)getpid());
	printf("%jd is saying: My child's pid=%d\n", (intmax_t)getpid(), pid);
	printf("%jd is saying: My parent's pid=%jd\n", (intmax_t)getpid(), (intmax_t)getppid());
	printf("%jd is saying: Doing some work...\n", (intmax_t)getpid());
	printf("%jd is saying: sleeping...\n", (intmax_t)getpid());
	sleep(5);
	printf("%jd is saying: Second fork()!\n\n", (intmax_t)getpid());
	pid = fork();

	printf("%jd is saying: Hello!\n", (intmax_t)getpid());
	printf("%jd is saying: My child's pid=%d\n", (intmax_t)getpid(), pid);
	printf("%jd is saying: My parent's pid=%jd\n", (intmax_t)getpid(), (intmax_t)getppid());
	printf("%jd is saying: Doing final work...\n", (intmax_t)getpid());
	printf("%jd is saying: Bye!\n", (intmax_t)getpid());
	return (0);
}
