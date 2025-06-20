/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:01:20 by kmonjard          #+#    #+#             */
/*   Updated: 2025/06/20 20:44:40 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	Helper function to keep the left overs of line_buffer.
	Returns NULL for malloc error.
*/
static char	*ft_keep_left_over(char *line_buffer)
{
	char	*out;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!line_buffer)
		return (NULL);
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	while (line_buffer[j] != '\0')
		j++;
	out = (char *)ft_calloc(j - i + 1, sizeof(char));
	if (!out)
		return (NULL);
	j = 0;
	i++;
	while (line_buffer[i])
		out[j++] = line_buffer[i++];
	out[j] = '\0';
	return (out);
}

/*
	Helper function that cuts down line buffer.
	Cuts down to only charcters before the '\n' or string end.
	Returns (NULL) for malloc error or empty line_buffer
*/
static char	*ft_extract_line(const char	*line_buffer)
{
	int		nl_flag;
	char	*line;
	size_t	i;

	i = 0;
	nl_flag = 0;
	if (!line_buffer || !line_buffer[i])
		return (NULL);
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\n')
		nl_flag = 1;
	line = (char *)ft_calloc(i + nl_flag + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
	{
		line[i] = line_buffer[i];
		i++;
	}
	if (line_buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/*
	Helper function to cut down line_buffer extraction.
	Function checks
*/
static char	*ft_extract_and_retain(char	**line_buffer)
{
	char	*line;
	char	*tmp;

	line = ft_extract_line(*line_buffer);
	tmp = ft_keep_left_over(*line_buffer);
	if (*line_buffer != tmp)
		ft_free_buffer(line_buffer);
	*line_buffer = tmp;
	return (line);
}

/*
	Helper function that reads file into the static buffer.
	Uses strjoin to combine read buffer into line buffer.
	Returns NULL for allocation fails & read fails.
*/
static char	*ft_read_file(int fd, char *line_buffer)
{
	char	*tmp;
	char	*buffer;
	ssize_t	read_bytes;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (ft_strchr_bool(line_buffer, '\n') == 0 && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		tmp = ft_strjoin(line_buffer, buffer);
		free(line_buffer);
		line_buffer = tmp;
	}
	if (read_bytes == -1)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (line_buffer);
}

char	*get_next_line(int fd)
{
	int			update_bool;
	char		*new_line;
	static char	*line_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		ft_free_buffer(&line_buffer);
		return (NULL);
	}
	if (!line_buffer)
		line_buffer = (char *)ft_calloc(1, sizeof(char));
	if (!line_buffer)
		return (NULL);
	update_bool = ft_update_buffer(fd, &line_buffer);
	if (!update_bool)
		return (NULL);
	new_line = ft_extract_and_retain(&line_buffer);
	return (new_line);
}
