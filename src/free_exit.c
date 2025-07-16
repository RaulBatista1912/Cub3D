/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:30:55 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/15 14:54:04 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_exit(t_data *data, int code)
{
	if (data->map->north_texture)
		free (data->map->north_texture);
	if (data->map->south_texture)
		free (data->map->south_texture);
	if (data->map->west_texture)
		free (data->map->west_texture);
	if (data->map->east_texture)
		free (data->map->east_texture);
	free_exit2(data, code);
}

void	free_exit2(t_data *data, int code)
{
	if (data->map->map)
		free_tab(data->map->map);
	if (data->map->tmp)
		free_tab(data->map->tmp);
	if (data->map)
		free (data->map);
	if (data->player)
		free (data->player);
	if (data->keys)
		free (data->keys);
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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}
