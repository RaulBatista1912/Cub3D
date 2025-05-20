/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:18:11 by rabatist          #+#    #+#             */
/*   Updated: 2025/05/20 17:42:22 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data_map_player(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return;
	data->mlx = NULL;
	data->win = NULL;
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_HEIGHT;
	init_map(data);
	init_player(data);
}

void	init_player(t_data *data)
{
	data->player->player_count = 0;
	data->player->pos_x = 0;
	data->player->pos_y = 0;
}

void	init_map(t_data *data)
{
	data->map->north_texture = NULL;
	data->map->south_texture = NULL;
	data->map->west_texture = NULL;
	data->map->east_texture = NULL;
	data->map->floor_color = 0;
	data->map->ceiling_color = 0;
	data->map->heightmap = 0;
	data->map->map = NULL;
	data->map->tmp = NULL;
	data->map->tmp2 = NULL;
}
