/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_texture_and_color.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:58:56 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/08 15:00:13 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extract_map_texture_and_color(t_map *map)
{
	int	i;

	i = -1;
	while (map->tmp[++i])
	{
		if (ft_strncmp(map->tmp[i], "NO ", 3) == 0)
		{
			map->north_texture = ft_strdup(ft_strchr(map->tmp[i], ' ') + 1);
			if (!map->north_texture)
				free_exit(map);
			map->north_texture[ft_strlen(map->north_texture) - 1] = '\0';
		}
	}
	i = -1;
	while (map->tmp[++i])
	{
		if (ft_strncmp(map->tmp[i], "SO ", 3) == 0)
		{
			map->south_texture = ft_strdup(ft_strchr(map->tmp[i], ' ') + 1);
			if (!map->south_texture)
				free_exit(map);
			map->south_texture[ft_strlen(map->south_texture) - 1] = '\0';
		}
	}
	extract_map_texture_and_color2(map);
}

void	extract_map_texture_and_color2(t_map *map)
{
	int	i;

	i = -1;
	while (map->tmp[++i])
	{
		if (ft_strncmp(map->tmp[i], "WE ", 3) == 0)
		{
			map->west_texture = ft_strdup(ft_strchr(map->tmp[i], ' ') + 1);
			if (!map->west_texture)
				free_exit(map);
			map->west_texture[ft_strlen(map->west_texture) - 1] = '\0';
		}
	}
	i = -1;
	while (map->tmp[++i])
	{
		if (ft_strncmp(map->tmp[i], "EA ", 3) == 0)
		{
			map->east_texture = ft_strdup(ft_strchr(map->tmp[i], ' ') + 1);
			if (!map->east_texture)
				free_exit(map);
			map->east_texture[ft_strlen(map->east_texture) - 1] = '\0';
		}
	}
	extract_map_texture_and_color3(map);
}

void	extract_map_texture_and_color3(t_map *map)
{
	int	i;

	i = 0;
	while (map->tmp[i])
	{
		if (ft_strncmp(map->tmp[i], "F ", 2) == 0)
			parse_color(map->tmp[i], &map->floor_color);
		else if (ft_strncmp(map->tmp[i], "C ", 2) == 0)
			parse_color(map->tmp[i], &map->ceiling_color);
		i++;
	}
}

int	extract_number(char *str, int *i)
{
	int	total;

	total = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		total = total * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (total);
}

void	parse_color(char *line, int *color)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 2;
	r = extract_number(line, &i);
	i++;
	g = extract_number(line, &i);
	i++;
	b = extract_number(line, &i);
	*color = (r << 16) | (g << 8) | b;
}