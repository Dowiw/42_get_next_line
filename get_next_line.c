/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:32:36 by kmonjard          #+#    #+#             */
/*   Updated: 2025/06/06 20:30:47 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Function that reads a line from file descriptor
char	*get_next_line(int fd)
{
	char		*buffer;
	char		*new_line;
	static char	*left_c;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	buffer = ft_read_file(fd, buffer, left_c);
	if (!buffer)
		return (NULL);
	new_line = ft_line_maker(buffer);
	left_c = ft_left_over(buffer);
	return (new_line);
}
