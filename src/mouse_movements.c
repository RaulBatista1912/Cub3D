/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaiah <isaiah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:27:35 by isaiah            #+#    #+#             */
/*   Updated: 2025/07/12 16:27:35 by isaiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	int		delta_x;
	double	angle;

	(void)y;
	if (data->player->last_mouse_x == -1)
	{
		data->player->last_mouse_x = x;
		return (0);
	}
	delta_x = x - data->player->last_mouse_x;
	if (delta_x > 50 || delta_x < -50)
	{
		data->player->last_mouse_x = x;
		return (0);
	}
	data->player->last_mouse_x = x;
	angle = 0.02 * delta_x;
	rotate(data, angle);
	return (0);
}
