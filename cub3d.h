/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:56:44 by rabatist          #+#    #+#             */
/*   Updated: 2025/04/04 17:51:04 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include <stdio.h>
# include "mlx/mlx.h"
# include "GNL/get_next_line.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;
}	t_data;

typedef struct s_map
{
	char	**map;
	int		map_height;
	char	**tmp;
	int		floor_color;
	int		ceiling_color;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		heightmap;
}	t_map;


int		check_arg(int ac, char **av);
int		is_dir(char *str);
int		is_openable(char *str);

//init.c
void	init_mlx(t_data *data);
void	init_data(t_data *data);
void	init_map(t_map *map);

//read_map.c
int		add_line(t_map *map, char *line);
void	read_map(t_map *map, char **av);
void	parse_map_color_and_texture(char *line, t_map *map);
void	parse_color(char *line, int *color);
void	parse_color(char *line, int *color);
void	extract_map(t_map *map);
void	extract_map2(t_map *map, int start);

#endif