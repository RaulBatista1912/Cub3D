/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:56:46 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/17 18:11:26 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	debug_de_ses_morts(t_map *map, t_player *player)
{
	int	i;

	i = 0;
	printf("map textures :\n");
	printf("C : %d\n", map->ceiling_color);
	printf("F : %d\n", map->floor_color);
	printf("NO : %s\n", map->north_texture);
	printf("SO : %s\n", map->south_texture);
	printf("WE : %s\n", map->west_texture);
	printf("EA : %s\n", map->east_texture);
	printf("player X,Y : %d,%d\n", player->player_x, player->player_y);
	printf("\nmap :\n");
	while (i < map->heightmap)
	{
		printf("%s", map->map[i]);
		i++;
	}
	printf("\n");
	printf("\ntmp :\n");
	i = 0;
	while (map->tmp[i])
	{
		printf("%s", map->tmp[i]);
		i++;
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	t_data		data;
	t_map		map;
	t_player	player;

	if (check_arg(ac, av))
		return (1);
	init_data(&data);
	init_map(&map);
	init_player(&player);
	read_map(&map, av);
	if (check_map_texture_and_color(&map))
		free_exit(&map, 1);
	extract_map_texture_and_color(&map);
	extract_map(&map);
	if (parse_map(&map, &player))
		free_exit(&map, 1);
	init_mlx(&data);
	debug_de_ses_morts(&map, &player);
	free_ptr(&data);
	free_exit(&map, 0);
}
