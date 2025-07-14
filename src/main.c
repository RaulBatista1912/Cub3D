/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:56:46 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/14 18:45:24 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* void	debug_de_ses_morts(t_data *data)
{
	int	i;

	i = 0;
	printf("map textures :\n");
	printf("C : %d\n", data->map->ceiling_color);
	printf("F : %d\n", data->map->floor_color);
	printf("NO : %s\n", data->map->north_texture);
	printf("SO : %s\n", data->map->south_texture);
	printf("WE : %s\n", data->map->west_texture);
	printf("EA : %s\n", data->map->east_texture);
	printf("player X,Y : %f,%f\n", data->player->pos_x, data->player->pos_y);
	printf("player is %c\n", data->player->player);
	printf("\nmap :\n");
	while (i < data->map->heightmap)
	{
		printf("%s", data->map->map[i]);
		i++;
	}
	printf("\n");
	printf("\ntmp :\n");
	i = 0;
	while (data->map->tmp[i])
	{
		printf("%s", data->map->tmp[i]);
		i++;
	}
	printf("\n");
} */

int	main(int ac, char **av)
{
	t_data	data;

	if (check_arg(ac, av))
		return (1);
	init_data_map_player(&data);
	read_map(&data, av);
	if (check_map_texture_and_color(&data))
		free_exit(&data, 1);
	extract_map_texture_and_color(&data);
	if (parse_map(&data))
		free_exit(&data, 1);
	start_game(&data);
}
