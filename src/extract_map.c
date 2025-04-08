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

