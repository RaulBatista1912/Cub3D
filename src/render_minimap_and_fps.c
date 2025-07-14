/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_and_fps.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:02:40 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/14 15:28:15 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(data->mlx, data->win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_data *data)
{
	int	x_start;
	int	y_start;
	int	i;
	int	j;

	x_start = WIN_WIDTH - data->map->widthmap * 10 - 20;
	y_start = WIN_HEIGHT - data->map->heightmap * 10 - 20;
	i = 0;
	while (i < data->map->heightmap)
	{
		j = 0;
		while (j < (int)ft_strlen(data->map->map[i]))
		{
			if (data->map->map[i][j] == '1')
				put_square(data, x_start + j * 10, y_start + i * 10, WHITE);
			else if (ft_strchr("0NSWE", data->map->map[i][j]))
				put_square(data, x_start + j * 10, y_start + i
					* 10, BLACK);
			j++;
		}
		i++;
	}
	put_circle(data, x_start + data->player->pos_x * 10,
		y_start + data->player->pos_y * 10, RED);
}

void	put_circle(t_data *data, int cx, int cy, int color)
{
	int	x;
	int	y;

	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			if (x * x + y * y <= 3 * 3)
				mlx_pixel_put(data->mlx, data->win,
					cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}

void	render_fps(t_data *data)
{
	struct timeval	tv;
	double			current_time;
	char			*fps_str;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
	data->fps.frames++;
	if (current_time - data->fps.last_time >= 1.0)
	{
		data->fps.fps = data->fps.frames
			/ (current_time - data->fps.last_time);
		data->fps.frames = 0;
		data->fps.last_time = current_time;
	}
	fps_str = ft_itoa((int)(data->fps.fps));
	mlx_string_put(data->mlx, data->win, 10, 10,
		0x00FF0000, "FPS: ");
	mlx_string_put(data->mlx, data->win, 50, 10,
		0x00FF0000, fps_str);
	free(fps_str);
}
