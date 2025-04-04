/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:54:15 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/04 18:28:38 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	add_line(t_map *map, char *line)
{
	int		i;
	char	**new_map;

	if (!line)
		return (1);
	new_map = malloc(sizeof(char *) * (map->heightmap + 2));
	if (!new_map)
		return (1);
	i = -1;
	while (++i < map->heightmap)
		new_map[i] = map->tmp[i];
	new_map[i] = ft_strdup(line);
	new_map[i + 1] = NULL;
	if (map->tmp)
		free(map->tmp);
	map->tmp = new_map;
	map->heightmap++;
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
		parse_map_color_and_texture(line_read, map);
		if (add_line(map, line_read))
		{
			free (line_read);
			break ;
		}
	}
	close (fd);
	extract_map(map);
}

