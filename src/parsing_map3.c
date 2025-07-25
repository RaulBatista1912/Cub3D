/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:35:29 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/25 17:33:05 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map_closed(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == '0')
			{
				if (y == 0 || x == 0 || !data->map->map[y + 1]
					|| x >= (int)ft_strlen(data->map->map[y - 1])
					|| x >= (int)ft_strlen(data->map->map[y + 1])
					|| x + 1 >= (int)ft_strlen(data->map->map[y])
					|| x - 1 < 0)
					return (1);
				if (check_map_closed2(data, x, y))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_map_closed2(t_data *data, int x, int y)
{
	if (data->map->map[y][x + 1] == ' ' || data->map->map[y][x + 1] == '\0'
		|| data->map->map[y][x - 1] == ' ' || data->map->map[y][x - 1] == '\0'
		|| data->map->map[y - 1][x] == ' ' || data->map->map[y - 1][x] == '\0'
		|| data->map->map[y + 1][x] == ' ' || data->map->map[y + 1][x] == '\0')
		return (1);
	return (0);
}
