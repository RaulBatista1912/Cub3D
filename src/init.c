/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaiah <isaiah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:18:11 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/12 16:08:17 by isaiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data_map_player(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return ;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return ;
	data->keys = malloc(sizeof(t_keys));
	if (!data->keys)
		return ;
	data->keys->w = 0;
	data->keys->a = 0;
	data->keys->s = 0;
	data->keys->d = 0;
	data->keys->left = 0;
	data->keys->right = 0;
	data->keys->esc = 0;
	data->mlx = NULL;
	data->win = NULL;
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_HEIGHT;
	init_map(data);
	init_player(data);
	init_textures(data);
}

void	init_player(t_data *data)
{
	data->player->player_count = 0;
	data->player->pos_x = 0;
	data->player->pos_y = 0;
	data->player->dir_x = 0;
	data->player->dir_y = 0;
	data->player->plane_x = 0;
	data->player->plane_y = 0;
	data->player->player = 0;
	data->player->last_mouse_x = -1;
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
	data->map->widthmap = 0;
	data->map->map = NULL;
	data->map->tmp = NULL;
	data->map->tmp2 = NULL;
	data->fps.frames = 0;
	data->fps.last_time = 0;
	data->fps.fps = 0;
	data->fps.str[0] = '\0';
}

void	init_textures(t_data *data)
{
	data->textures.north = NULL;
	data->textures.south = NULL;
	data->textures.west = NULL;
	data->textures.east = NULL;
	data->textures.north_addr = NULL;
	data->textures.south_addr = NULL;
	data->textures.west_addr = NULL;
	data->textures.east_addr = NULL;
	data->textures.width = 0;
	data->textures.height = 0;
	data->textures.bpp = 0;
	data->textures.line_len = 0;
	data->textures.endian = 0;
}
