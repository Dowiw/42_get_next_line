/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:32:36 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/26 16:32:39 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Function that reads a line from file descriptor
char	*get_next_line(int fd)
{
	static char	**buffer_array;
	char	*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	buffer_array = malloc();
	fill_array(buffer_array, fd);
}

// Fill buffer array with buffers
int	fill_array(char **buffer_array, int fd)
{
	size_t	file_chars;
	char	*buffer;
	int		concat_flag;

	while (!ft_strchr(buffer_array))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		file_chars = read(fd, buffer, BUFFER_SIZE);
		buffer[file_chars] = '\0';
		concat_flag = concat_buffer(buffer_array, buffer);
	}
}

// Add buffer to buffer array
int	concat_buffer(char **buffer_array, char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer_array[i] != NULL)
		i++;
	buffer_array[i] = buffer;
	buffer_array[++i] = NULL;
}

//Find char c in string s: return first found address, NULL otherwise
char	*ft_bufferchr(const char **s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
