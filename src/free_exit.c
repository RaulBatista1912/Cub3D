/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:30:55 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/09 16:18:16 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_exit(t_map *map, int code)
{
	if (map->north_texture)
		free (map->north_texture);
	if (map->south_texture)
		free (map->south_texture);
	if (map->west_texture)
		free (map->west_texture);
	if (map->east_texture)
		free (map->east_texture);
	free_exit2(map, code);
}

void	free_exit2(t_map *map, int code)
{
	int	i;

	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free (map->map[i]);
			i++;
		}
		free (map->map);
	}
	if (map->tmp)
	{
		i = 0;
		while (map->tmp[i])
		{
			free (map->tmp[i]);
			i++;
		}
		free (map->tmp);
	}
	exit (code);
}

void	free_ptr(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free (data->mlx);
	}
}
