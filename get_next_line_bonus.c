/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:06:18 by kmonjard          #+#    #+#             */
/*   Updated: 2025/06/17 10:29:03 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Function that reads a line from file descriptor
char	*get_next_line(int fd)
{
	char		*buffer;
	char		*new_line;
	static char	*left_c[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer = ft_read_file(fd, buffer, left_c[fd]);
	if (!buffer)
	{
		free(buffer);
		free(left_c[fd]);
		return (NULL);
	}
	new_line = ft_line_maker(buffer);
	left_c[fd] = ft_left_over(buffer);
	return (new_line);
}
