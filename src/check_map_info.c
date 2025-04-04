#include "../cub3d.h"

int	check_map_info(t_map *map)
{
	if (check_texture_and_color(map))
		return (1);
	
}

int	check_texture_and_color(t_map *map)
{
	if (map->ceiling_color == 0)
	{

	}
	if (map->floor_color == 0)
	{
		
	}
}