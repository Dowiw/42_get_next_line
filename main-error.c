#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main() {
	int fd = open("small.txt", O_RDONLY);

	char *test;

	while ((test = get_next_line(fd)) != NULL) {
		printf("line: %s", test);
		free(test);	
	}

	close(fd);
	fd = open("small.txt", O_RDONLY);
	while ((test = get_next_line(fd)) != NULL) {
		printf("line: %s", test);
		free(test);
	}
	close(fd);
}
