/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:51:50 by rabatist          #+#    #+#             */
/*   Updated: 2025/08/13 12:56:25 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map_texture_and_color(t_data *data)
{
	if (check_no_texture(data))
		return (1);
	if (check_so_texture(data))
		return (1);
	if (check_we_texture(data))
		return (1);
	if (check_ea_texture(data))
		return (1);
	if (check_c_color(data))
		return (1);
	if (check_f_color(data))
		return (1);
	if (check_rgb_format(data))
	{
		ft_putstr_fd("Error\nWrong RGB format\n", 2);
		return (1);
	}
	return (0);
}

int	check_no_texture(t_data *data)
{
	int		i;
	int		tmp;
	char	*line;

	i = -1;
	tmp = 0;
	while (data->map->tmp[++i])
	{
		line = data->map->tmp[i];
		while (*line == ' ' || *line == '\t')
			line++;
		if (ft_strncmp(line, "NO ", 3) == 0)
			tmp++;
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

int	check_so_texture(t_data *data)
{
	int		i;
	int		tmp;
	char	*line;

	i = -1;
	tmp = 0;
	while (data->map->tmp[++i])
	{
		line = data->map->tmp[i];
		while (*line == ' ' || *line == '\t')
			line++;
		if (ft_strncmp(line, "SO ", 3) == 0)
			tmp++;
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

int	check_we_texture(t_data *data)
{
	int		i;
	int		tmp;
	char	*line;

	i = -1;
	tmp = 0;
	while (data->map->tmp[++i])
	{
		line = data->map->tmp[i];
		while (*line == ' ' || *line == '\t')
			line++;
		if (ft_strncmp(line, "WE ", 3) == 0)
			tmp++;
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

int	check_ea_texture(t_data *data)
{
	int		i;
	int		tmp;
	char	*line;

	i = -1;
	tmp = 0;
	while (data->map->tmp[++i])
	{
		line = data->map->tmp[i];
		while (*line == ' ' || *line == '\t')
			line++;
		if (ft_strncmp(line, "EA ", 3) == 0)
			tmp++;
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
