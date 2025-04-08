/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:54:15 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/08 14:35:16 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	add_line(t_map *map, char *line)
{
	int		i;

	if (!line)
		return (1);
	map->heightmap++;
	map->tmp2 = (char **)malloc(sizeof(char *) * (map->heightmap + 1));
	if (!map->tmp2)
		free_exit(map);
	i = 0;
	while (i < map->heightmap - 1)
	{
		map->tmp2[i] = map->tmp[i];
		i++;
	}
	map->tmp2[map->heightmap - 1] = line;
	map->tmp2[map->heightmap] = NULL;
	if (map->tmp)
		free (map->tmp);
	map->tmp = map->tmp2;
	return (0);
}

void	read_map(t_map *map, char **av)
{
	char	*line_read;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFile cannot be open\n", 2);
		exit (1);
	}
	while (1)
	{
		line_read = get_next_line(fd);
		if (!line_read)
			break ;
		if (add_line(map, line_read))
		{
			free (line_read);
			break ;
		}
	}
	close (fd);
}

