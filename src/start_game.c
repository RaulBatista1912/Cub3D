/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:06:07 by rabatist          #+#    #+#             */
/*   Updated: 2025/05/20 19:05:01 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(t_data *data)
{
	free(data->mlx);
	exit(0);
}

void	start_game(t_data *data)
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
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, render_frame_wrapper, data);
	mlx_loop(data->mlx);
}

int render_frame_wrapper(void *param)
{
	t_data *data = (t_data *)param;
	render_frame(data);
	return (0);
}
void put_pixel(t_img *img, int x, int y, int color)
{
	char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void render_frame(t_data *data)
{
	t_img		frame;
	double		posX = data->player->pos_x + 0.5;
	double		posY = data->player->pos_y + 0.5;
	double		dirX = 0;
	double		dirY = -1;
	double		planeX = 2;
	double		planeY = 0;

	// Création d’une image
	frame.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_len, &frame.endian);

	for (int x = 0; x < WIN_WIDTH; x++)
	{
		double cameraX = 2.0 * x / WIN_WIDTH - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		int mapX = (int)posX;
		int mapY = (int)posY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);

		int stepX, stepY;
		double sideDistX, sideDistY;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		int hit = 0;
		int side;
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map->map[mapY][mapX] == '1')
				hit = 1;
		}

		double perpWallDist;
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

		for (int y = 0; y < drawStart; y++)
			put_pixel(&frame, x, y, data->map->ceiling_color);

		for (int y = drawEnd; y < WIN_HEIGHT; y++)
			put_pixel(&frame, x, y, data->map->floor_color);
	}

	mlx_put_image_to_window(data->mlx, data->win, frame.img, 0, 0);
	mlx_destroy_image(data->mlx, frame.img);
}
