# 42_get_next_line
This project is about programming a function that returns a line read from a file descriptor.

![image](https://github.com/user-attachments/assets/fe2c4e82-c428-40ad-b114-a3fc941e5a89)

Finished and mandatory function got moulinette evaluated! However, the bonus did not compile.

The function
`
char  *get_next_line(int fd);
`
should be able to:
- read from a file descriptor
- be able to return a line
  (a string of text where there is a new line at the end as if you pressed "Enter")
- compile with the -D (define) option where BUFFER_SIZE can be set from 1 to what limit..? **Hint: size_t**
- return (null) when file reaches EOF (end of file)

notes:
- compile your code as follows:
`
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<from 1 to preferred number> <file_names>.c
`
- must exhibit undefined behavior if file is modified after the last call
  (basically, when there are file changes before EOF, must have error)
- file must exhibit undefined behavior for binary files
  (this basically means, we don't know what will happen if binary files are read)
- **if the get_next_line call is stopped before the EOF the static variable will result in leaks**
- only malloc, read, and free is allowed. the end.

> with C and motivation,
kmonjard
