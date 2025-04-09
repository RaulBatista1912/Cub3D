/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:20:30 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/09 16:23:25 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_map(t_map *map, t_player *player)
{
	if (check_map_closed(map))
	{
		ft_putstr_fd("Error:\nMap not closed\n", 2);
		return (1);
	}
	if (parse_the_player(map, player))
		return (1);
	return (0);
}

int	parse_the_player(t_map *map, t_player *player)
{
	int	x;
	int	y;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
			if (map->map[y][x] == 'N' || map->map[y][x] == 'W' ||
				map->map[y][x] == 'S' || map->map[y][x] == 'E')
				player->player_count++;
	}
	if (player->player_count > 1)
	{
		ft_putstr_fd("Error:\nOnly One player needed\n", 2);
		return (1);
	}
	else if (player->player_count == 0)
	{
		ft_putstr_fd("Error:\nOne player needed\n", 2);
		return (1);
	}
	return (0);
}


int	check_map_closed(t_map *map)
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
