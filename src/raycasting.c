/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaiah <isaiah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:04:07 by isaiah            #+#    #+#             */
/*   Updated: 2025/07/12 16:06:05 by isaiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - ray->pos_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->wall_dist = (ray->map_y - ray->pos_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
}

void	init_values(int *line_height, int *draw_start,
		int *draw_end, t_ray *ray)
{
	*line_height = (int)(WIN_HEIGHT / ray->wall_dist * 0.8);
	*draw_start = -(*line_height) / 2 + WIN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = *line_height / 2 + WIN_HEIGHT / 2;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}
