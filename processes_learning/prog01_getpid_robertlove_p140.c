#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys/types.h>

/* intmax_t - largest signed integer type available */
int	main(void)
{
	printf("My pid=%jd\n", (intmax_t)getpid());
	printf("Parent's pid=%jd\n", (intmax_t)getppid());
	exit(0);
	return (0);
}
