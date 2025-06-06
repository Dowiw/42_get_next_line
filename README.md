# 42_get_next_line
This project is about programming a function that returns a line read from a file descriptor.

The function
`
char  *get_next_line(int fd);
`
should be able to:
- read from a file descriptor
- be able to return a line
  (a string of text where there is a new line at the end as if you pressed "Enter")
- compile with the -D (define) option where BUFFER_SIZE can be set from 1 to what limit..?
- return (null) when file reaches EOF (end of file)

notes:
- helpers should be contained only in `get_next_line_utils.c` so 5 functions
- compile your code as follows
`
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <file_names>.c
`
- must exhibit undefined behavior if file is modified after the last call
basically, when there are file changes before EOF, must have error
- file must exhibit undefined behavior for binary files
- only malloc, read, and free is allowed. the end.

with motivation,
kmonjard
