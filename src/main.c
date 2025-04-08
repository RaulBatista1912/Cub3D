/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:56:46 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/08 15:01:34 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;
	
	if (check_arg(ac, av))
		return (1);
	init_data(&data);
	init_map(&map);
	read_map(&map, av);
	if (check_map_texture_and_color(&map))
		free_exit(&map);
	extract_map_texture_and_color(&map);
	extract_map(&map);
	init_mlx(&data);

	printf("map textures :\n");
	printf("%d\n", map.ceiling_color);
	printf("%d\n", map.floor_color);
	printf("%s\n", map.north_texture);
	printf("%s\n", map.south_texture);
	printf("%s\n", map.west_texture);
	printf("%s\n", map.east_texture);

	printf("\nmap :\n");
	int	i = 0;
	while (i < map.heightmap)
	{
		printf("%s", map.map[i]);
		i++;
	}
	printf("\n");
	printf("\ntmp :\n");

	i = 0;
	while (map.tmp[i])
	{
		printf("%s", map.tmp[i]);
		i++;
	}
	printf("\n");
	
	free_ptr(&data);
	free_exit(&map);
	return (0);
}
