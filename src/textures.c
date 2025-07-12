/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaiah <isaiah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:43:08 by isaiah            #+#    #+#             */
/*   Updated: 2025/07/12 16:19:43 by isaiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_north_textures(t_data *data, int *width, int *height)
{
	data->textures.north = mlx_xpm_file_to_image(data->mlx,
			data->map->north_texture,
			width, height);
	if (!data->textures.north)
		return (0);
	data->textures.north_addr = mlx_get_data_addr(data->textures.north,
			&data->textures.bpp,
			&data->textures.line_len,
			&data->textures.endian);
	if (!data->textures.north_addr)
		return (0);
	return (1);
}

int	load_south_textures(t_data *data, int *width, int *height)
{
	data->textures.width = *width;
	data->textures.height = *height;
	data->textures.south = mlx_xpm_file_to_image(data->mlx,
			data->map->south_texture,
			width, height);
	if (!data->textures.south)
		return (0);
	data->textures.south_addr = mlx_get_data_addr(data->textures.south,
			&data->textures.bpp,
			&data->textures.line_len,
			&data->textures.endian);
	if (!data->textures.south_addr)
		return (0);
	return (1);
}

int	load_west_textures(t_data *data, int *width, int *height)
{
	data->textures.west = mlx_xpm_file_to_image(data->mlx,
			data->map->west_texture,
			width, height);
	if (!data->textures.west)
		return (0);
	data->textures.west_addr = mlx_get_data_addr(data->textures.west,
			&data->textures.bpp,
			&data->textures.line_len,
			&data->textures.endian);
	if (!data->textures.west_addr)
		return (0);
	return (1);
}

int	load_east_textures(t_data *data, int *width, int *height)
{
	data->textures.east = mlx_xpm_file_to_image(data->mlx,
			data->map->east_texture,
			width, height);
	if (!data->textures.east)
		return (0);
	data->textures.east_addr = mlx_get_data_addr(data->textures.east,
			&data->textures.bpp,
			&data->textures.line_len,
			&data->textures.endian);
	if (!data->textures.east_addr)
		return (0);
	return (1);
}

int	load_textures(t_data *data)
{
	int	width;
	int	height;

	if (!load_north_textures(data, &width, &height))
		return (0);
	if (!load_south_textures(data, &width, &height))
	{
		mlx_destroy_image(data->mlx, data->textures.north);
		return (0);
	}
	if (!load_west_textures(data, &width, &height))
	{
		mlx_destroy_image(data->mlx, data->textures.north);
		mlx_destroy_image(data->mlx, data->textures.south);
		return (0);
	}
	if (!load_east_textures(data, &width, &height))
	{
		mlx_destroy_image(data->mlx, data->textures.north);
		mlx_destroy_image(data->mlx, data->textures.south);
		mlx_destroy_image(data->mlx, data->textures.west);
		return (0);
	}
	return (1);
}
