/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_color_and_xpm.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:13:59 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/10 14:21:44 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_c_color(t_map *map)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (map->tmp[i])
	{
		if (ft_strncmp(map->tmp[i], "C ", 2) == 0)
			tmp++;
		i++;
	}
	if (tmp == 0)
	{
		ft_putstr_fd("Error\nCeiling color missing\n", 2);
		return (1);
	}
	else if (tmp > 1)
	{
		ft_putstr_fd("Error\nMultiple Ceiling color\n", 2);
		return (1);
	}
	return (0);
}

int	check_f_color(t_map *map)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (map->tmp[i])
	{
		if (ft_strncmp(map->tmp[i], "F ", 2) == 0)
			tmp++;
		i++;
	}
	if (tmp == 0)
	{
		ft_putstr_fd("Error\nFloor color missing\n", 2);
		return (1);
	}
	else if (tmp > 1)
	{
		ft_putstr_fd("Error\nMultiple Floor color\n", 2);
		return (1);
	}
	return (0);
}

int	check_if_xpm(t_map *map)
{
	if (ft_strlen(map->north_texture) < 5 || ft_strncmp(map->north_texture
			+ ft_strlen(map->north_texture) - 4, ".xpm", 4) != 0)
		return (1);
	if (ft_strlen(map->south_texture) < 5 || ft_strncmp(map->south_texture
			+ ft_strlen(map->south_texture) - 4, ".xpm", 4) != 0)
		return (1);
	if (ft_strlen(map->west_texture) < 5 || ft_strncmp(map->west_texture
			+ ft_strlen(map->west_texture) - 4, ".xpm", 4) != 0)
		return (1);
	if (ft_strlen(map->east_texture) < 5 || ft_strncmp(map->east_texture
			+ ft_strlen(map->east_texture) - 4, ".xpm", 4) != 0)
		return (1);
	return (0);
}
