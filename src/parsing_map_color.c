/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:13:59 by rabatist          #+#    #+#             */
/*   Updated: 2025/07/14 15:31:30 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_c_color(t_data *data)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (data->map->tmp[i])
	{
		if (ft_strncmp(data->map->tmp[i], "C ", 2) == 0)
			tmp++;
		i++;
	}
	if (tmp == 0)
	{
		ft_putstr_fd("Error\nCeiling color missing\n", 2);
		return (1);
	}
	else if (tmp > 1)
	{
		ft_putstr_fd("Error\nMultiple Ceiling color\n", 2);
		return (1);
	}
	return (0);
}

int	check_f_color(t_data *data)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (data->map->tmp[i])
	{
		if (ft_strncmp(data->map->tmp[i], "F ", 2) == 0)
			tmp++;
		i++;
	}
	if (tmp == 0)
	{
		ft_putstr_fd("Error\nFloor color missing\n", 2);
		return (1);
	}
	else if (tmp > 1)
	{
		ft_putstr_fd("Error\nMultiple Floor color\n", 2);
		return (1);
	}
	return (0);
}

int	check_rgb_format(t_data *data)
{
	int	i;

	i = 0;
	while (data->map->tmp[i])
	{
		if (ft_strncmp(data->map->tmp[i], "F ", 2) == 0
			|| ft_strncmp(data->map->tmp[i], "C ", 2) == 0)
		{
			if (check_rgb_line(data->map->tmp[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_rgb_line(char *line)
{
	int		i;
	char	**split;

	i = 2;
	while (line[i] == ' ')
		i++;
	split = ft_split(line + i, ',');
	if (!split)
		return (1);
	i = 0;
	while (split[i])
		i++;
	if (i != 3 || is_valid_rgb(split))
	{
		free_tab(split);
		return (1);
	}
	free_tab(split);
	return (0);
}

int	is_valid_rgb(char **str)
{
	int		i;
	int		numb;
	char	*trimmed;

	i = 0;
	while (str[i])
	{
		trimmed = ft_strtrim(str[i], " \t\n\r");
		if (!trimmed)
			return (1);
		if (!is_str_digit(trimmed))
		{
			free(trimmed);
			return (1);
		}
		numb = ft_atoi(trimmed);
		if (numb < 0 || numb > 255)
		{
			free(trimmed);
			return (1);
		}
		free(trimmed);
		i++;
	}
	return (0);
}
