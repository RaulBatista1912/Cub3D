/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_texture_and_color.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:58:56 by rabatist          #+#    #+#             */
/*   Updated: 2025/05/08 17:28:03 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extract_map_texture_and_color(t_data *data)
{
	int	i;

	i = -1;
	while (data->map->tmp[++i])
	{
		if (ft_strncmp(data->map->tmp[i], "NO ", 3) == 0)
		{
			data->map->north_texture = ft_strdup(ft_strchr(data->map->tmp[i], ' ') + 1);
			if (!data->map->north_texture)
				free_exit(data, 1);
			data->map->north_texture[ft_strlen(data->map->north_texture) - 1] = '\0';
		}
	}
	i = -1;
	while (data->map->tmp[++i])
	{
		if (ft_strncmp(data->map->tmp[i], "SO ", 3) == 0)
		{
			data->map->south_texture = ft_strdup(ft_strchr(data->map->tmp[i], ' ') + 1);
			if (!data->map->south_texture)
				free_exit(data, 1);
			data->map->south_texture[ft_strlen(data->map->south_texture) - 1] = '\0';
		}
	}
	extract_map_texture_and_color2(data);
}

void	extract_map_texture_and_color2(t_data *data)
{
	int	i;

	i = -1;
	while (data->map->tmp[++i])
	{
		if (ft_strncmp(data->map->tmp[i], "WE ", 3) == 0)
		{
			data->map->west_texture = ft_strdup(ft_strchr(data->map->tmp[i], ' ') + 1);
			if (!data->map->west_texture)
				free_exit(data, 1);
			data->map->west_texture[ft_strlen(data->map->west_texture) - 1] = '\0';
		}
	}
	i = -1;
	while (data->map->tmp[++i])
	{
		if (ft_strncmp(data->map->tmp[i], "EA ", 3) == 0)
		{
			data->map->east_texture = ft_strdup(ft_strchr(data->map->tmp[i], ' ') + 1);
			if (!data->map->east_texture)
				free_exit(data, 1);
			data->map->east_texture[ft_strlen(data->map->east_texture) - 1] = '\0';
		}
	}
	extract_map_texture_and_color3(data);
}

void	extract_map_texture_and_color3(t_data *data)
{
	int	i;

	i = 0;
	while (data->map->tmp[i])
	{
		if (ft_strncmp(data->map->tmp[i], "F ", 2) == 0)
			parse_color(data->map->tmp[i], &data->map->floor_color);
		else if (ft_strncmp(data->map->tmp[i], "C ", 2) == 0)
			parse_color(data->map->tmp[i], &data->map->ceiling_color);
		i++;
	}
	extract_map(data);
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
