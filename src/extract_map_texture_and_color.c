/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_texture_and_color.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:58:56 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/14 17:29:53 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extract_map_texture_and_color(t_data *data)
{
	data->map->north_texture = extractor(data, "NO ");
	data->map->south_texture = extractor(data, "SO ");
	data->map->west_texture = extractor(data, "WE ");
	data->map->east_texture = extractor(data, "EA ");
	extract_map_texture_and_color2(data);
	extract_map(data);
}

char	*extractor(t_data *data, char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (data->map->tmp[i])
	{
		if (ft_strncmp(data->map->tmp[i], str, 3) == 0)
		{
			line = ft_strdup(ft_strchr(data->map->tmp[i], ' ') + 1);
			if (!line)
				free_exit(data, 1);
			line[ft_strlen(line) - 1] = '\0';
		}
		i++;
	}
	return (line);
}

void	extract_map_texture_and_color2(t_data *data)
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
	skip_whitespace(line, &i);
	r = extract_number(line, &i);
	skip_whitespace(line, &i);
	i++;
	skip_whitespace(line, &i);
	g = extract_number(line, &i);
	skip_whitespace(line, &i);
	i++;
	skip_whitespace(line, &i);
	b = extract_number(line, &i);
	*color = (r << 16) | (g << 8) | b;
}
