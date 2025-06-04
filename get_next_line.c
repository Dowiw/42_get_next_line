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

static char	*ft_left_over(char	*buffer)
{
	char	*out;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	out = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	i++;
	while (buffer[i])
	{
		out[j] = buffer[i];
		i++;
		j++;
	}
	out[j] = '\0';
	free(buffer);
	return (out);
}

// Helper to create the line (not for leftover)
static char	*ft_line_maker(char *buffer)
{
	int		nl_flag;
	char	*line;
	size_t	i;

	i = 0;
	nl_flag = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		nl_flag = 1;
	line = malloc(sizeof(char) * (i + nl_flag + 1));
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

// Helper for main logic to read line into buffer and retain leftovers
static char	*ft_read_file(int fd, char *buffer, char *left_c)
{
	char	*temp;
	ssize_t	out_bytes;

	out_bytes = 1;
	while (out_bytes > 0)
	{
		out_bytes = read(fd, buffer, BUFFER_SIZE);
		if (out_bytes == -1)
			break ;
		buffer[out_bytes] = '\0';
		temp = ft_strjoin(left_c, buffer);
		free(left_c);
		left_c = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (left_c);
}

// Helper function to help prepare buffer & leftovers to be checked
static char	*ft_line_prep(int fd, char *left_c)
{
	char	*buffer;
	char	*out;

	if (!left_c)
	{
		left_c = malloc(sizeof(char) * 1);
		left_c[0] = '\0';
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	out = ft_read_file(fd, buffer, left_c);
	return (out);
}

// Function that reads a line from file descriptor
char	*get_next_line(int fd)
{
	static char	*left_c;
	char	*buffer;
	char	*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_line_prep(fd, left_c);
	if (!buffer)
		return (NULL);
	new_line = ft_line_maker(buffer);
	left_c = ft_left_over(buffer);
	return (new_line);
}

