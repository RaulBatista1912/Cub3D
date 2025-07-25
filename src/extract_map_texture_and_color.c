/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_texture_and_color.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:58:56 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/25 17:31:14 by rabatist         ###   ########.fr       */
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
	char	*j;

	i = -1;
	while (data->map->tmp[++i])
	{
		j = data->map->tmp[i];
		while (*j == ' ' || *j == '\t')
			j++;
		if (ft_strncmp(j, str, 2) == 0 && (j[2] == ' ' || j[2] == '\t'))
		{
			j += 2;
			while (*j == ' ' || *j == '\t' || *j == ':')
				j++;
			line = ft_strdup(j);
			if (!line)
				free_exit(data, 1);
			if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			remove_white_space_at_the_end(line);
			return (line);
		}
	}
	return (NULL);
}

void	extract_map_texture_and_color2(t_data *data)
{
	int		i;
	char	*j;

	i = 0;
	while (data->map->tmp[i])
	{
		j = data->map->tmp[i];
		while (*j == ' ' || *j == '\t')
			j++;
		if (ft_strncmp(j, "F ", 2) == 0)
			parse_color(j, &data->map->floor_color);
		else if (ft_strncmp(j, "C ", 2) == 0)
			parse_color(j, &data->map->ceiling_color);
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
	skip_whitespace_and_comma(line, &i);
	r = extract_number(line, &i);
	skip_whitespace_and_comma(line, &i);
	g = extract_number(line, &i);
	skip_whitespace_and_comma(line, &i);
	b = extract_number(line, &i);
	*color = (r << 16) | (g << 8) | b;
}
