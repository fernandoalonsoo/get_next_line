/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:18:48 by fernando          #+#    #+#             */
/*   Updated: 2024/12/31 17:18:51 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_check_remainder(char **remainder);
static void	ft_remainder(int fd, char *buffer, size_t bytes, char **remainder);

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*buffer;
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	ft_remainder(fd, buffer, bytes_read, &remainder);
	line = ft_check_remainder(&remainder);
	return (line);
}

static char	*ft_end(char *line)
{
	if (!line)
		return (NULL);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	else
		return (line);
}

static char	*ft_check_remainder(char **remainder)
{
	char	*line;
	size_t	len;
	char	*aux;

	if (!(*remainder))
		return (NULL);
	len = 0;
	while ((*remainder)[len] != '\n' && (*remainder)[len])
		len++;
	line = NULL;
	if ((*remainder)[len] == '\n')
	{
		line = ft_substr(*remainder, 0, len + 1);
		aux = ft_strdup(*remainder + len + 1);
		free(*remainder);
		*remainder = aux;
		return (line);
	}
	line = ft_strdup(*remainder);
	free(*remainder);
	*remainder = NULL;
	return (ft_end(line));
}

static void	ft_remainder(int fd, char *buffer, size_t bytes, char **remainder)
{
	char	*aux;

	buffer[bytes] = '\0';
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		if (!(*remainder))
			*remainder = ft_strdup("");
		aux = ft_strjoin(*remainder, buffer);
		free(*remainder);
		*remainder = aux;
		if (ft_strchr(*remainder, '\n'))
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
}
