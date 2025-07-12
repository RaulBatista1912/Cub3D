/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaiah <isaiah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:33:03 by isaiah            #+#    #+#             */
/*   Updated: 2025/07/12 15:33:52 by isaiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_ray_dir(t_data *data, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2.0 * x / WIN_WIDTH - 1.0;
	ray->pos_x = data->player->pos_x;
	ray->pos_y = data->player->pos_y;
	ray->dir_x = data->player->dir_x + data->player->plane_x * camera_x;
	ray->dir_y = data->player->dir_y + data->player->plane_y * camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
}

void	init_ray_side_distances(t_ray *ray)
{
	if (ray->dir_x < 0)
		ray->side_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	else
		ray->side_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;
	if (ray->dir_y < 0)
		ray->side_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	else
		ray->side_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
}

void	init_ray_deltas(t_ray *ray)
{
	ray->delta_x = fabs(1.0 / ray->dir_x);
	ray->delta_y = fabs(1.0 / ray->dir_y);
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}
