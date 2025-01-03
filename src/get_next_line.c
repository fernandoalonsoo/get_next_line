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

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*buffer;
	ssize_t		bytes_read;
	char		*line;
	char		*aux;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	if (remainder && ft_strchr(remainder, '\n'))
	{
		free(buffer);
		return (ft_check_remainder(&remainder));
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		aux = ft_strjoin(remainder, buffer);
		if (!aux)
		{
			free(remainder);
			free(buffer);
			return (NULL);
		}
		free(remainder);
		remainder = aux;
		if (ft_strchr(remainder, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read == 0 && remainder && *remainder)
	{
		line = ft_strdup(remainder);
		free(remainder);
		remainder = NULL;
		return (line);
	}
	else if (bytes_read < 0)
		return (NULL);
	line = ft_check_remainder(&remainder);
	return (line);
}

static char	*ft_check_remainder(char **remainder)
{
	char	*line;
	size_t	len;
	char	*aux;

	len = 0;
	if (!*remainder || **remainder == '\0')
		return (NULL);
	while ((*remainder)[len] != '\n')
		len++;
	line = NULL;
	if (len == ft_strlen(*remainder))
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		remainder = NULL;
		return (line);
	}
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
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("prueba2.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free (line);
// 		line = get_next_line(fd);
// 	}
// 	if (fd >= 0)
// 		close(fd);
// 	return (0);
// }