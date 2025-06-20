#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

// cc -Wall -Werror -Wextra main.c get_next_line.c get_next_line_utils.c
// valgrind --leak-check=full ./a.out

/*
	IMPORTANT:
	When files are read and gnl exits prematurely,
	it will not free the static buffer.
	This results in a leak of the last line.
*/
int main() {
	int fd = open("lorem.txt", O_RDONLY);

	char *line_eng;
	int i = 0;
	while ((line_eng = get_next_line(fd)) != NULL)
	{
		printf("line %i: %s", i, line_eng);
		free(line_eng);
		i++;
	}

	close(fd);
	return (0);
}
