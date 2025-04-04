/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:56:46 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/04 17:54:03 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_dir(char *str)
{
	int	fd;

	fd = open(str, __O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		return (1);
	}
	return (0);
}

int	is_openable(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	check_arg(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage : ./Cub3D maps/*.cub\n", 2);
		return (1);
	}
	if (ft_strlen(av[1]) < 5
		|| ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nWrong map format, *.cub needed\n", 2);
		return(1);
	}
	if (is_dir(av[1]))
	{
		ft_putstr_fd("Error\nFile is a directory\n", 2);
		return (1);
	}
	if(is_openable(av[1]))
	{
		ft_putstr_fd("Error\nFile cannot be open\n", 2);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;
	
	if (check_arg(ac, av))
		return (1);
	init_data(&data);
	init_map(&map);
	init_mlx(&data);
	read_map(&map, av);

	printf("%d\n", map.ceiling_color);
	printf("%d\n", map.floor_color);
	printf("%s\n", map.north_texture);
	printf("%s\n", map.south_texture);
	printf("%s\n", map.west_texture);
	printf("%s\n", map.east_texture);

	printf("\n\n\n");
	int	i = 0;
	while (i < map.heightmap)
	{
		printf("%s", map.tmp[i]);
		i++;
	}
	printf("\n");
	return (0);
}
