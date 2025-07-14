/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:34:04 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/14 15:29:21 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_invalid(char c)
{
	return (c == ' ' || c == '\n' || c == '\0');
}

int	check_if_player_inside(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map->map[++y])
	{
		x = -1;
		while (data->map->map[y][++x])
		{
			if (data->map->map[y][x] == 'N' || data->map->map[y][x] == 'W' ||
				data->map->map[y][x] == 'S' || data->map->map[y][x] == 'E')
			{
				if (!data->map->map[y + 1] || y == 0 || !data->map->map[y - 1]
					|| !data->map->map[y][x + 1] || x == 0
					|| !data->map->map[y][x - 1])
					return (1);
				if (is_invalid(data->map->map[y][x + 1]) ||
					is_invalid(data->map->map[y][x - 1]) ||
					is_invalid(data->map->map[y + 1][x]) ||
					is_invalid(data->map->map[y - 1][x]))
					return (1);
			}
		}
	}
	return (0);
}

int	check_if_xpm(t_data *data)
{
	if (ft_strlen(data->map->north_texture) < 5
		|| ft_strncmp(data->map->north_texture
			+ ft_strlen(data->map->north_texture) - 4, ".xpm", 4) != 0)
		return (1);
	if (ft_strlen(data->map->south_texture) < 5
		|| ft_strncmp(data->map->south_texture
			+ ft_strlen(data->map->south_texture) - 4, ".xpm", 4) != 0)
		return (1);
	if (ft_strlen(data->map->west_texture) < 5
		|| ft_strncmp(data->map->west_texture
			+ ft_strlen(data->map->west_texture) - 4, ".xpm", 4) != 0)
		return (1);
	if (ft_strlen(data->map->east_texture) < 5
		|| ft_strncmp(data->map->east_texture
			+ ft_strlen(data->map->east_texture) - 4, ".xpm", 4) != 0)
		return (1);
	return (0);
}

void	get_player_dir(t_data *data)
{
	if (data->player->player == 'N')
	{
		data->player->dir_x = 0;
		data->player->dir_y = -1;
		data->player->plane_x = 1;
		data->player->plane_y = 0;
	}
	else if (data->player->player == 'S')
	{
		data->player->dir_x = 0;
		data->player->dir_y = 1;
		data->player->plane_x = -1;
		data->player->plane_y = 0;
	}
}

void	get_player_dir2(t_data *data)
{
	if (data->player->player == 'E')
	{
		data->player->dir_x = 1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = 1;
	}
	else if (data->player->player == 'W')
	{
		data->player->dir_x = -1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = -1;
	}
}
