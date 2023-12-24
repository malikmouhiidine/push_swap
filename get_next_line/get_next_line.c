/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:19:10 by mmouhiid          #+#    #+#             */
/*   Updated: 2023/11/25 18:29:54 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char	*free_handler(char *buffer, char *line, char **remainder)
{
	if (buffer)
		free(buffer);
	if (line)
		free(line);
	if (remainder && *remainder)
	{
		free(*remainder);
		*remainder = NULL;
	}
	return (NULL);
}

void	join_handler(char **tmp, char **line, char **buffer)
{
	*tmp = *line;
	*line = ft_strjoin(*line, *buffer);
	free(*tmp);
}

char	*read_handler(int fd, char *line)
{
	ssize_t			ret;
	char			*tmp;
	char			*buffer;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_handler(NULL, line, NULL));
	ret = read(fd, buffer, BUFFER_SIZE);
	buffer[ret] = '\0';
	join_handler(&tmp, &line, &buffer);
	if (!line)
		return (free_handler(buffer, NULL, NULL));
	while (!ft_strchr(line, '\n') && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		buffer[ret] = '\0';
		join_handler(&tmp, &line, &buffer);
		if (!line)
			return (free_handler(buffer, NULL, NULL));
	}
	free(buffer);
	return (line);
}

char	*return_handler(char **line, char **tmp, char **remainder)
{
	if (ft_strchr(*line, '\n'))
	{
		*tmp = *line;
		if (ft_strchr(*line, '\n') - *line < (long)ft_strlen(*line))
		{
			*remainder = ft_strdup(ft_strchr(*line, '\n') + 1);
			if (!*remainder)
				return (free_handler(NULL, *line, NULL));
		}
		else
			*remainder = NULL;
		*line = ft_substr(*line, 0, ft_strchr(*line, '\n') + 1 - *line);
		free(*tmp);
		if (!*line)
			return (free_handler(NULL, NULL, &*remainder));
	}
	if (!ft_strlen(*line))
		return (free_handler(NULL, *line, NULL));
	return (*line);
}

char	*get_next_line(int fd)
{
	static char		*remainder;
	char			*line;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free_handler(NULL, NULL, &remainder));
	if (remainder)
	{
		line = ft_strdup(remainder);
		free(remainder);
		remainder = NULL;
	}
	else
		line = ft_strdup("");
	if (!line)
		return (NULL);
	line = read_handler(fd, line);
	if (!line)
		return (free_handler(NULL, NULL, &remainder));
	return (return_handler(&line, &tmp, &remainder));
}
