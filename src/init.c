/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:18:11 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/09 16:00:35 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_HEIGHT;
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

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		exit (1);
	}
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
	{
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		free (data->mlx);
		exit (1);
	}
}
