/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:18:11 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/19 16:31:58 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data_map_player(t_data *data, t_map *map, t_player *player)
{
	data->mlx = NULL;
	data->win = NULL;
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_HEIGHT;
	init_map(map);
	init_player(player);
}

void	init_player(t_player *player)
{
	player->player_count = 0;
	player->player_x = 0;
	player->player_y = 0;
}

void	init_map(t_map *map)
{
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->west_texture = NULL;
	map->east_texture = NULL;
	map->floor_color = 0;
	map->ceiling_color = 0;
	map->heightmap = 0;
	map->map = NULL;
	map->tmp = NULL;
	map->tmp2 = NULL;
}
