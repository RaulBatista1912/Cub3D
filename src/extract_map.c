/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:53:58 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/04 14:58:08 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extract_map(t_data *data)
{
	int	start;

	start = 0;
	while (data->map->tmp[start])
	{
		if (!(ft_strncmp(data->map->tmp[start], "NO ", 3) == 0
				|| ft_strncmp(data->map->tmp[start], "SO ", 3) == 0
				|| ft_strncmp(data->map->tmp[start], "WE ", 3) == 0
				|| ft_strncmp(data->map->tmp[start], "EA ", 3) == 0
				|| ft_strncmp(data->map->tmp[start], "F ", 2) == 0
				|| ft_strncmp(data->map->tmp[start], "C ", 2) == 0))
		{
			if (ft_strchr(data->map->tmp[start], '1'))
				break ;
		}
		start++;
	}
	extract_map2(data, start);
}

void	extract_map2(t_data *data, int start)
{
	int		i;

	i = start;
	data->map->heightmap = 0;
	while (data->map->tmp[i])
	{
		data->map->heightmap++;
		i++;
	}
	data->map->map = malloc(sizeof(char *) * (data->map->heightmap + 1));
	if (!data->map->map)
		return ;
	i = 0;
	while (i < data->map->heightmap)
	{
		data->map->map[i] = ft_strdup(data->map->tmp[start + i]);
		i++;
	}
	data->map->map[i] = NULL;
	extract_map_width(data, start);
}

void extract_map_width(t_data *data, int start)
{
	int	max;
	int	current;

	max = 0;
	while (data->map->tmp[start])
	{
		current = ft_strlen(data->map->tmp[start]);
		if (max < current)
			max = current;
		start++;
	}
	data->map->widthmap = max;
}
