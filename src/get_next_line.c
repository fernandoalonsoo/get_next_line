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

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	if (remainder && ft_strchr(remainder, '\n'))
		return (ft_check_remainder(&remainder));
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		if (ft_strchr(remainder, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read <= 0)
	{
		if (remainder && *remainder)
		{
			line = ft_strdup(remainder);
			free(remainder);
			remainder = NULL;
			return (line);
		}
		free(buffer);
		return (NULL);
	}
	free(buffer);
	line = ft_check_remainder(&remainder);
	return (line);
}

static char	*ft_check_remainder(char **remainder)
{
	char	*line;
	char	*aux;
	int		len;

	len = 0;
	if (!*remainder || **remainder == '\0')
		return (NULL);
	while ((*remainder)[len] != '\n')
		len++;
	line = malloc(len + 2);
	if (!line)
		return (NULL);
	if ((*remainder)[len] == '\n')
	{
		line = ft_substr(*remainder, 0, len + 1);
		aux = ft_strdup(*remainder + len + 1);
		if (!line || !aux)
			return (NULL);
	}
	else
		aux = NULL;
	free(*remainder);
	*remainder = aux;
	return (line);
}

/*int main()
{
	int fd; 

	fd = open("../prueba2.txt", O_RDONLY);
	if (fd == -1)
		return 1;
	
	int i = 0;
	char *line;
	while (line = get_next_line(fd))
        printf("%s", line);  				
	
	free(line);          					
	printf("\nCapacidad del buffer: %d", BUFFER_SIZE);
	close(fd);
	return 0;
}*/