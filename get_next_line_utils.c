/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:11:47 by kmonjard          #+#    #+#             */
/*   Updated: 2025/06/20 20:45:08 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_file(int fd, char *line_buffer)
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

void	ft_free_buffer(char **line_buffer)
{
	if (line_buffer && *line_buffer)
	{
		free(*line_buffer);
		*line_buffer = NULL;
	}
}

int	ft_strchr_bool(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*out;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	out = malloc(sizeof(char) * (i + j + 1));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		out[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		out[j++] = s2[i++];
	out[j] = '\0';
	return (out);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*out;
	size_t			i;
	size_t			total;
	unsigned char	*setter;

	if (nmemb == 0 || size == 0)
		return (NULL);
	total = nmemb * size;
	out = malloc(nmemb * size);
	if (!out)
		return (NULL);
	setter = out;
	i = 0;
	while (i < total)
		setter[i++] = 0;
	return (out);
}
