/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:54:15 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/10 16:46:02 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	add_line(t_data *data, char *line)
{
	int		i;

	if (!line)
		return (1);
	data->map->heightmap++;
	data->map->tmp2 = (char **)malloc(sizeof(char *)
			* (data->map->heightmap + 1));
	if (!data->map->tmp2)
		free_exit(data, 1);
	i = 0;
	while (i < data->map->heightmap - 1)
	{
		data->map->tmp2[i] = data->map->tmp[i];
		i++;
	}
	data->map->tmp2[data->map->heightmap - 1] = line;
	data->map->tmp2[data->map->heightmap] = NULL;
	if (data->map->tmp)
		free (data->map->tmp);
	data->map->tmp = data->map->tmp2;
	return (0);
}

void	read_map(t_data *data, char **av)
{
	char	*line_read;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFile could not be open\n", 2);
		exit (1);
	}
	while (1)
	{
		line_read = get_next_line(fd);
		if (!line_read)
			break ;
		if (add_line(data, line_read))
		{
			free (line_read);
			break ;
		}
	}
	close (fd);
}
