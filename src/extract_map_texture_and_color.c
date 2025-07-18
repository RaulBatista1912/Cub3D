/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_texture_and_color.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:58:56 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/18 18:11:13 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extract_map_texture_and_color(t_data *data)
{
	data->map->north_texture = extractor(data, "NO");
	data->map->south_texture = extractor(data, "SO");
	data->map->west_texture = extractor(data, "WE");
	data->map->east_texture = extractor(data, "EA");
	extract_map_texture_and_color2(data);
	extract_map(data);
}

char	*extractor(t_data *data, char *str)
{
	char	*line;
	int		i;
	char	*start;

	i = 0;
	while (data->map->tmp[i])
	{
		start = data->map->tmp[i];
		while (*start == ' ' || *start == '\t')
			start++;
		if (ft_strncmp(start, str, 2) == 0 && (start[2] == ' ' || start[2] == '\t'))
		{
			start += 2;
			while (*start == ' ' || *start == '\t' || *start == ':')
				start++;
			line = ft_strdup(start);
			if (!line)
				free_exit(data, 1);
			if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			remove_white_space_at_the_end(line);
			return (line);
		}
		i++;
	}
	return (NULL);
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
