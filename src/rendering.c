/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaiah <isaiah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:23:13 by isaiah            #+#    #+#             */
/*   Updated: 2025/07/12 16:37:00 by isaiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_texture_position(t_draw_info *info, t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		info->wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		info->wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
	info->wall_x -= floor(info->wall_x);
	info->tex_x = (int)(info->wall_x * (double)data->textures.width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		info->tex_x = data->textures.width - info->tex_x - 1;
}

void	get_texture_addr(t_draw_info *info, t_ray *ray, t_data *data)
{
	if (ray->side == 0 && ray->dir_x > 0)
		info->texture_addr = data->textures.east_addr;
	else if (ray->side == 0 && ray->dir_x < 0)
		info->texture_addr = data->textures.west_addr;
	else if (ray->side == 1 && ray->dir_y > 0)
		info->texture_addr = data->textures.south_addr;
	else
		info->texture_addr = data->textures.north_addr;
}

void	draw_textured_wall(t_draw_info *info, t_data *data,
					t_img *frame, int x)
{
	info->step = 1.0 * data->textures.height / info->line_height;
	info->tex_pos = (info->draw_start - WIN_HEIGHT / 2
			+ info->line_height / 2) * info->step;
	info->y = info->draw_start;
	while (info->y <= info->draw_end)
	{
		info->tex_y = (int)info->tex_pos & (data->textures.height - 1);
		info->tex_pos += info->step;
		info->color = *(unsigned int *)(info->texture_addr
				+ (info->tex_y * data->textures.line_len
					+ info->tex_x * (data->textures.bpp / 8)));
		put_pixel(frame, x, info->y, info->color);
		info->y++;
	}
}

void	draw_ceiling_floor(t_draw_info *info, t_data *data,
	t_img *frame, int x)
{
	info->y = 0;
	while (info->y < info->draw_start)
		put_pixel(frame, x, info->y++, data->map->ceiling_color);
	info->y = info->draw_end + 1;
	while (info->y < WIN_HEIGHT)
		put_pixel(frame, x, info->y++, data->map->floor_color);
}

void	textures_handle(t_draw_info *info, t_ray *ray,
		t_data *data, t_img *frame)
{
	init_values(&info->line_height, &info->draw_start, &info->draw_end, ray);
	init_texture_position(info, ray, data);
	get_texture_addr(info, ray, data);
	draw_textured_wall(info, data, frame, data->frame_tools.frame_x);
	draw_ceiling_floor(info, data, frame, data->frame_tools.frame_x);
}

void	draw_column(t_data *data, t_img *frame, t_ray *ray)
{
	t_draw_info	info;

	textures_handle(&info, ray, data, frame);
}
