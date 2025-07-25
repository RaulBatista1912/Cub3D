/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:53:58 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/25 17:26:40 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extract_map(t_data *data)
{
	int		start;
	char	*line;

	start = 0;
	while (data->map->tmp[start])
	{
		line = data->map->tmp[start];
		while (*line == ' ' || *line == '\t')
			line++;
		if (!(ft_strncmp(line, "NO ", 3) == 0
				|| ft_strncmp(line, "SO ", 3) == 0
				|| ft_strncmp(line, "WE ", 3) == 0
				|| ft_strncmp(line, "EA ", 3) == 0
				|| ft_strncmp(line, "F ", 2) == 0
				|| ft_strncmp(line, "C ", 2) == 0))
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
		if (data->map->tmp[i][0] == '\n')
			break ;
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

void	extract_map_width(t_data *data, int start)
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
	data->map->widthmap = max - 1;
}
