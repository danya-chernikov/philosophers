#include <stdio.h>
#include <stdlib.h>

void	out(void)
{
	printf("atexit() succeeded!\n");
}

int	main(void)
{
	if (atexit(out))
		fprintf(stderr, "atexit() failed!\n");
	printf("Doing some things...\n");
	return (0);
}
