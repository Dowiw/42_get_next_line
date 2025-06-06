/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:33:21 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/26 16:33:22 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Find char c in string s: return first found address, NULL otherwise
char	*ft_strchr(const char *s, int c)
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

//Concatinates s1 (prefix) to s2 (suffix) (strings unfreed)
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	out = malloc(sizeof(char) * (i + j + 1));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		out[j++] = s1[i++];
	i = 0;
	while (s2[i])
		out[j++] = s2[i++];
	out[j] = '\0';
	return (out);
}

// Helper function to retain leftovers for next line
char	*ft_left_over(char	*buffer)
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
	while (buffer[j] != '\0')
		j++;
	out = malloc(sizeof(char) * (j - i + 1));
	j = 0;
	i++;
	while (buffer[i])
		out[j++] = buffer[i++];
	out[j] = '\0';
	free(buffer);
	return (out);
}

// Helper to create the line (not for leftover)
char	*ft_line_maker(char *buffer)
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
char	*ft_read_file(int fd, char *buffer, char *left_c)
{
	char	*temp;
	ssize_t	out_bytes;

	if (!left_c)
	{
		left_c = malloc(sizeof(char) * 1);
		left_c[0] = '\0';
	}
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
