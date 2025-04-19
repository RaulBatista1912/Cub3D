/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:34:04 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/19 16:01:32 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_if_player_inside(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'W' ||
				map->map[y][x] == 'S' || map->map[y][x] == 'E')
			{
				if (!map->map[y + 1] || y == 0 || !map->map[y - 1]
					|| !map->map[y][x + 1] || x == 0 || !map->map[y][x - 1])
					return (1);
				if (map->map[y][x + 1] == ' ' || map->map[y][x - 1] == ' ' ||
					map->map[y + 1][x] == ' ' || map->map[y - 1][x] == ' ')
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_if_xpm(t_map *map)
{
	if (ft_strlen(map->north_texture) < 5 || ft_strncmp(map->north_texture
			+ ft_strlen(map->north_texture) - 4, ".xpm", 4) != 0)
		return (1);
	if (ft_strlen(map->south_texture) < 5 || ft_strncmp(map->south_texture
			+ ft_strlen(map->south_texture) - 4, ".xpm", 4) != 0)
		return (1);
	if (ft_strlen(map->west_texture) < 5 || ft_strncmp(map->west_texture
			+ ft_strlen(map->west_texture) - 4, ".xpm", 4) != 0)
		return (1);
	if (ft_strlen(map->east_texture) < 5 || ft_strncmp(map->east_texture
			+ ft_strlen(map->east_texture) - 4, ".xpm", 4) != 0)
		return (1);
	return (0);
}
