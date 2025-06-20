#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

// cc -Wall -Werror -Wextra main.c get_next_line.c get_next_line_utils.c
// valgrind --leak-check=full ./a.out

int main(void)
{
	int fd1 = open("lorem.txt", O_RDONLY);
	int fd2 = open("lorem_deutsch.txt", O_RDONLY);
	char *line1 = NULL;
	char *line2 = NULL;
	int i = 0;
	int done1 = 0, done2 = 0;

	while (!done1 || !done2)
	{
		if (!done1 && (line1 = get_next_line(fd1)))
		{
			printf("line %d: %s", i, line1);
			free(line1);
		}
		else
			done1 = 1;
		if (!done2 && (line2 = get_next_line(fd2)))
		{
			printf("line %d: %s", i, line2);
			free(line2);
		}
		else
			done2 = 1;
		i++;
	}
	close(fd1);
	close(fd2);
	return 0;
}

/*
	IMPORTANT:
	When files are read, when one file reaches EOF, it will continue reading the other file.
	This results in a leak of the last line of the file that reached EOF.
	Because the static buffer is not freed until the next call to get_next_line.
*/
// int main() {
// 	int fd = open("lorem.txt", O_RDONLY);
// 	int fd2 = open("lorem_deutsch.txt", O_RDONLY);

// 	char *line_eng;
// 	char *line_de;
// 	int i = 0;
// 	while ((line_eng = get_next_line(fd)) != NULL && (line_de = get_next_line(fd2)) != NULL) {
// 		printf("line %i: %s", i, line_eng);
// 		printf("line %i: %s", i, line_de);
// 		free(line_eng);
// 		free(line_de);
// 		i++;
// 	}
// 	free(line_eng);
// 	free(line_de);
// 	line_eng = get_next_line(fd);
// 	printf("eof? %i: %s", i, line_eng);
// 	free(line_eng);

// 	char *line1german = get_next_line(fd);
// 	printf("line1: %s", line1german);
// 	free(line1german);

// 	free(line_eng);
// 	close(fd);
// 	return (0);
// }
