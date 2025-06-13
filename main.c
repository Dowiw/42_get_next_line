#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

// cc -Wall -Werror -Wextra main.c get_next_line.c get_next_line_utils.c
int main() {
	int fd = open("lorem_deutsch.txt", O_RDONLY);
	int fd2 = open("lorem.txt", O_RDONLY);

	char *line1eng = get_next_line(fd2);
	int i = 0;
	while ((line1eng = get_next_line(fd2)) != NULL)
	{
		printf("line %i: %s", i, line1eng);
		free(line1eng);
		i++;
	}
	line1eng = get_next_line(fd2);
	printf("eof? %i: %s", i, line1eng);
	free(line1eng);

	// char *line1german = get_next_line(fd);
	// printf("line1: %s", line1german);
	// free(line1german);

	close(fd);
	return (0);
}
