/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:13:59 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/19 16:00:51 by rabatist         ###   ########.fr       */
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
