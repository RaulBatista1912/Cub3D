/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:20:30 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/08 19:31:22 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map_closed(t_map *map)
{
	if (parse_map(map))
	{
		printf("Error:\nMap not closed\n");
		return (1);
	}
	return (0);
}

int	parse_map(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '0')
			{
				if (!map->map[y][x + 1] || !map->map[y][x - 1] ||
					!map->map[y + 1][x] || !map->map[y - 1][x])
					return (1);
				if (map->map[y][x + 1] == ' ' || map->map[y][x + 1] == '\n' ||
					map->map[y][x - 1] == ' ' || map->map[y][x - 1] == '\n' ||
					map->map[y - 1][x] == ' ' || map->map[y - 1][x] == '\n' ||
					map->map[y + 1][x] == ' ' || map->map[y + 1][x] == '\n')
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
