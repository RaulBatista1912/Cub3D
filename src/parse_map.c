#include "../cub3d.h"

void	extract_map(t_map *map)
{
	int	start;

	start = 0;
	while (map->tmp[start])
	{
		if (!(ft_strncmp(map->tmp[start], "NO ", 3) == 0 ||
				ft_strncmp(map->tmp[start], "SO ", 3) == 0 ||
				ft_strncmp(map->tmp[start], "WE ", 3) == 0 ||
				ft_strncmp(map->tmp[start], "EA ", 3) == 0 ||
				ft_strncmp(map->tmp[start], "F ", 2) == 0 ||
				ft_strncmp(map->tmp[start], "C ", 2) == 0))
		{
			if (ft_strchr(map->tmp[start], '1'))
				break;
		}
		start++;
	}
	extract_map2(map, start);
}

void	extract_map2(t_map *map, int start)
{
	int		i;

	i = start;
	map->heightmap = 0;
	while (map->tmp[i])
	{
		map->heightmap++;
		i++;
	}
	map->map = malloc(sizeof(char *) * (map->heightmap + 1));
	if (!map->map)
		return ;
	i = 0;
	while (i < map->heightmap)
	{
		map->map[i] = ft_strdup(map->tmp[start + i]);
		i++;
	}
	map->map[i] = NULL;
}

void	parse_map_color_and_texture(char *line, t_map *map)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		map->north_texture = ft_strdup(ft_strchr(line, ' ') + 1);
		map->north_texture[ft_strlen(map->north_texture) - 1] = '\0';
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		map->south_texture = ft_strdup(ft_strchr(line, ' ') + 1);
		map->south_texture[ft_strlen(map->south_texture) - 1] = '\0';
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		map->west_texture = ft_strdup(ft_strchr(line, ' ') + 1);
		map->west_texture[ft_strlen(map->west_texture) - 1] = '\0';
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		map->east_texture = ft_strdup(ft_strchr(line, ' ') + 1);
		map->east_texture[ft_strlen(map->east_texture) - 1] = '\0';
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line, &map->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line, &map->ceiling_color);
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
