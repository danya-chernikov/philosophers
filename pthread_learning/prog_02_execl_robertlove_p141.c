#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int	main(void)
{
	int	ret;

	ret = execl("/bin/vi", "vi", "just_a_file.txt", NULL);
	if (ret == -1)
		perror("execl");
	exit(0);
	return (0);
}
