/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:20:30 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/14 15:38:07 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_map(t_data *data)
{
	if (check_map_closed(data))
	{
		ft_putstr_fd("Error\nMap not closed\n", 2);
		return (1);
	}
	if (parse_the_player(data))
		return (1);
	if (check_if_only_valid_character(data))
		return (1);
	if (check_if_player_inside(data))
	{
		ft_putstr_fd("Error\nPlayer is not inside the map\n", 2);
		return (1);
	}
	if (check_if_xpm(data))
	{
		ft_putstr_fd("Error\nTexture with format *.xpm needed\n", 2);
		return (1);
	}
	get_player_pos(data);
	get_player_dir(data);
	get_player_dir2(data);
	return (0);
}

int	check_if_only_valid_character(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] != 'N' && data->map->map[y][x] != 'W' &&
				data->map->map[y][x] != 'S' && data->map->map[y][x] != 'E' &&
				data->map->map[y][x] != '1' && data->map->map[y][x] != '0' &&
				data->map->map[y][x] != ' ' && data->map->map[y][x] != '\t' &&
				data->map->map[y][x] != '\n' && data->map->map[y][x] != '\r')
			{
				ft_putstr_fd("Error\nThere is an unvalid map element\n", 2);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	get_player_pos(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == 'N' || data->map->map[y][x] == 'W' ||
				data->map->map[y][x] == 'S' || data->map->map[y][x] == 'E')
			{
				data->player->pos_x = x + 0.5;
				data->player->pos_y = y + 0.5;
				data->player->player = data->map->map[y][x];
				break ;
			}
			x++;
		}
		y++;
	}
}

int	parse_the_player(t_data *data)
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
				data->player->player_count++;
		}
	}
	if (data->player->player_count > 1)
	{
		ft_putstr_fd("Error\nOnly One player needed\n", 2);
		return (1);
	}
	else if (data->player->player_count == 0)
	{
		ft_putstr_fd("Error\nOne player needed\n", 2);
		return (1);
	}
	return (0);
}
