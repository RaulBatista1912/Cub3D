/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:06:07 by rabatist          #+#    #+#             */
/*   Updated: 2025/05/08 16:44:23 by rabatist         ###   ########.fr       */
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
	mlx_loop(data->mlx);
}
