/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:05:30 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/07 19:29:37 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	str = malloc((ft_strlen(buffer) - i) * sizeof(char));
	if (!str)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = malloc((i + 2) * sizeof(char));
	else
		line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_join_and_free(char *sbuf, char *buf)
{
	char	*str;

	if (!sbuf)
	{
		sbuf = malloc(1);
		if (!sbuf)
			return (NULL);
		sbuf[0] = '\0';
	}
	str = ft_strjoin(sbuf, buf);
	free(sbuf);
	return (str);
}

char	*read_file(int fd, char *sbuf)
{
	char	*buffer;
	int		char_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	char_read = 1;
	while (char_read > 0)
	{
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read == -1)
		{
			free(buffer);
			free(sbuf);
			return (NULL);
		}
		buffer[char_read] = '\0';
		sbuf = ft_join_and_free(sbuf, buffer);
		if (ft_strchr(sbuf, '\n'))
			break ;
	}
	free(buffer);
	return (sbuf);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	if (!line)
	{
		free (buffer);
		buffer = (NULL);
		return (NULL);
	}
	buffer = clean_buffer(buffer);
	return (line);
}
/*
#include <stdio.h>

int	main()
{
	int		fd;
	char	*line;
	int		lines;

	lines = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%d : %s", lines++, line);
		free (line);
	}
}
*/
