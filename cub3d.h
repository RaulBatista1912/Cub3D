/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:56:44 by rabatist          #+#    #+#             */
/*   Updated: 2025/05/08 16:24:33 by irobinso         ###   ########.fr       */
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

typedef struct s_player
{
	int		player_x;
	int		player_y;
	int		player_count;
	char	player;
}	t_player;

typedef struct s_map
{
	char	**map;
	char	**tmp;
	char	**tmp2;
	int		floor_color;
	int		ceiling_color;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		heightmap;
}	t_map;

//parsing_arg.c
int		is_dir(char *str);
int		is_openable(char *str);
int		check_arg(int ac, char **av);

//parsing_map.c
int		parse_map(t_map *map, t_player *player);
void	get_player_info(t_map *map, t_player *player);
int		parse_the_player(t_map *map, t_player *s_player);
int		check_map_closed(t_map *map);
int		check_if_only_valid_character(t_map *map);

//parsing_map2.c
int		check_if_xpm(t_map *map);
int		check_if_player_inside(t_map *map);

//parsing_map_color.c
int		check_c_color(t_map *map);
int		check_f_color(t_map *map);

//parsing_map_texture.c
int		check_map_texture_and_color(t_map *map);
int		check_no_texture(t_map *map);
int		check_so_texture(t_map *map);
int		check_we_texture(t_map *map);
int		check_ea_texture(t_map *map);

//extract_map_texture_and_color.c
void	extract_map_texture_and_color(t_map *map);
void	extract_map_texture_and_color2(t_map *map);
void	extract_map_texture_and_color3(t_map *map);
int		extract_number(char *str, int *i);
void	parse_color(char *line, int *color);

//extract_map.c
void	extract_map(t_map *map);
void	extract_map2(t_map *map, int start);

//free_exit.c
void	free_exit(t_map *map, int code);
void	free_exit2(t_map *map, int code);
void	free_ptr(t_data *data);

//init.c
void	init_data_map_player(t_data *data, t_map *map, t_player *player);
void	init_map(t_map *map);
void	init_player(t_player *player);
void	init_mlx(t_data *data);

//read_map.c
int		add_line(t_map *map, char *line);
void	read_map(t_map *map, char **av);

//start_game.c
void	start_game(t_data *data);

void	debug_de_ses_morts(t_map *map, t_player *player);

#endif
