/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:55:07 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/14 15:55:38 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
