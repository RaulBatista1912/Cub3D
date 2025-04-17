/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:01:38 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/09 18:57:51 by rabatist         ###   ########.fr       */
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
		return (1);
	}
	if (is_dir(av[1]))
	{
		ft_putstr_fd("Error\nFile is a directory\n", 2);
		return (1);
	}
	if (is_openable(av[1]))
	{
		ft_putstr_fd("Error\nFile cannot be open\n", 2);
		return (1);
	}
	return (0);
}
