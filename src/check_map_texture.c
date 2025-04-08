#include "../cub3d.h"

int	check_map_texture_and_color(t_map *map)
{
	if (check_NO_texture(map))
		return (1);
	if (check_SO_texture(map))
		return (1);
	if (check_WE_texture(map))
		return (1);
	if (check_EA_texture(map))
		return (1);
	if (check_C_color(map))
		return (1);
	if (check_F_color(map))
		return (1);
	return (0);
}

int	check_NO_texture(t_map *map)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (map->tmp[i])
	{
		if (ft_strncmp(map->tmp[i], "NO ", 3) == 0)
			tmp++;
		i++;
	}
	if (tmp == 0)
	{
		ft_putstr_fd("Error\nNO texture missing\n", 2);
		return (1);
	}
	else if (tmp > 1)
	{
		ft_putstr_fd("Error\nMultiple NO texture\n", 2);
		return (1);
	}
	return (0);
}

int	check_SO_texture(t_map *map)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (map->tmp[i])
	{
		if (ft_strncmp(map->tmp[i], "SO ", 3) == 0)
			tmp++;
		i++;
	}
	if (tmp == 0)
	{
		ft_putstr_fd("Error\nSO texture missing\n", 2);
		return (1);
	}
	else if (tmp > 1)
	{
		ft_putstr_fd("Error\nMultiple SO texture\n", 2);
		return (1);
	}
	return (0);
}

int	check_WE_texture(t_map *map)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (map->tmp[i])
	{
		if (ft_strncmp(map->tmp[i], "WE ", 3) == 0)
			tmp++;
		i++;
	}
	if (tmp == 0)
	{
		ft_putstr_fd("Error\nWE texture missing\n", 2);
		return (1);
	}
	else if (tmp > 1)
	{
		ft_putstr_fd("Error\nMultiple WE texture\n", 2);
		return (1);
	}
	return (0);
}

int	check_EA_texture(t_map *map)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (map->tmp[i])
	{
		if (ft_strncmp(map->tmp[i], "EA ", 3) == 0)
			tmp++;
		i++;
	}
	if (tmp == 0)
	{
		ft_putstr_fd("Error\nEA texture missing\n", 2);
		return (1);
	}
	else if (tmp > 1)
	{
		ft_putstr_fd("Error\nMultiple EA texture\n", 2);
		return (1);
	}
	return (0);
}
