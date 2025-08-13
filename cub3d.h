/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:56:44 by rabatist          #+#    #+#             */
/*   Updated: 2025/08/13 12:24:18 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "mlx/mlx.h"
# include "GNL/get_next_line.h"

# define WIN_WIDTH 1600
# define WIN_HEIGHT 1000
# define PLAYER_SIZE 10
# define COLLISION_RADIUS 0.15

typedef enum e_color
{
	BLACK = 0x000000,
	WHITE = 0xFFFFFF,
	RED = 0xFF0000,
	GREEN = 0x00FF00,
	BLUE = 0x0000FF,
	YELLOW = 0xFFFF00,
	CYAN = 0x00FFFF,
	MAGENTA = 0xFF00FF,
	GREY = 0x808080,
	DARKGREY = 0x303030,
	ORANGE = 0xFFA500,
	BROWN = 0x8B4513
}	t_color;

typedef struct t_frame_tools
{
	int		frame_x;
}	t_frame_tools;

typedef struct s_draw_info
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;
	char	*texture_addr;
}	t_draw_info;

typedef struct s_ray
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	double		wall_dist;
}	t_ray;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	int			esc;
}	t_keys;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			player_count;
	char		player;
	int			last_mouse_x;
	int			mouse_ignore_next_move;
}	t_player;

typedef struct s_map
{
	char		**map;
	char		**tmp;
	char		**tmp2;
	int			floor_color;
	int			ceiling_color;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			heightmap;
	int			widthmap;
}	t_map;

typedef struct s_textures
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
	int		width;
	int		height;
	char	*north_addr;
	char	*south_addr;
	char	*west_addr;
	char	*east_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_textures;

typedef struct s_fps
{
	int		frames;
	double	last_time;
	double	fps;
	char	str[32];
}	t_fps;

typedef struct s_minimap
{
	int	x_start;
	int	y_start;
	int	square_size;
	int	width;
	int	height;
}	t_minimap;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	int				win_width;
	int				win_height;
	t_map			*map;
	t_player		*player;
	t_keys			*keys;
	t_textures		textures;
	t_fps			fps;
	t_minimap		minimap;
	t_frame_tools	frame_tools;
}	t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

//parsing_arg.c
int		is_dir(char *str);
int		is_openable(char *str);
int		check_arg(int ac, char **av);

//parsing_map.c
int		parse_map(t_data *data);
void	get_player_pos(t_data *data);
int		parse_the_player(t_data *data);
int		check_if_only_valid_character(t_data *data);

//parsing_map2.c
int		is_invalid(char c);
int		check_if_xpm(t_data *data);
int		check_if_player_inside(t_data *data);
void	get_player_dir(t_data *data);
void	get_player_dir2(t_data *data);

//parsing_map3.c
int		check_map_closed(t_data *data);
int		check_map_closed2(t_data *data, int x, int y);

//parsing_map_color.c
int		check_c_color(t_data *data);
int		check_f_color(t_data *data);
int		check_rgb_format(t_data *data);
int		check_rgb_line(char *line); //new
int		is_valid_rgb(char **str); //new

//parsing_map_texture.c
int		check_map_texture_and_color(t_data *data);
int		check_no_texture(t_data *data);
int		check_so_texture(t_data *data);
int		check_we_texture(t_data *data);
int		check_ea_texture(t_data *data);

//extract_map_texture_and_color.c
void	extract_map_texture_and_color(t_data *data);
void	extract_map_texture_and_color2(t_data *data);
char	*extractor(t_data *data, char *str);
int		extract_number(char *str, int *i);
void	parse_color(char *line, int *color); //new

//extract_map.c
void	extract_map(t_data *data);
void	extract_map2(t_data *data, int start);
void	extract_map_width(t_data *data, int start);

//free_exit.c
void	free_exit(t_data *data, int code);
void	free_exit2(t_data *data, int code);
void	free_ptr(t_data *data);
void	free_tab(char **tab);

//init.c
void	init_data_map_player(t_data *data);
void	init_map(t_data *data);
void	init_player(t_data *data);
void	init_mlx(t_data *data);
void	init_textures(t_data *data);

//read_map.c
int		add_line(t_data *data, char *line);
void	read_map(t_data *data, char **av);

//player_movements.c
void	move_player(t_data *data);
void	rotate(t_data *data, double angle);

//mouse_movement.c
int		mouse_move(int x, int y, t_data *data);

//tool.c
int		close_window(t_data *data);
int		handle_keypress(int keycode, t_data *data);
int		handle_keyrelease(int keycode, t_data *data);
void	skip_whitespace_and_comma(char *str, int *i); //new
int		is_str_digit(char *s); //new

//tools2.c
void	remove_white_space_at_the_end(char *line);

//raycasting2.c
void	init_ray_deltas(t_ray *ray);
void	init_ray_side_distances(t_ray *ray);
void	calculate_ray_dir(t_data *data, int x, t_ray *ray);

//raycasting.c
void	dda(t_data *data, t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_column(t_data *data, t_img *frame, t_ray *ray);

//rendering.c
void	textures_handle(t_draw_info *info, t_ray *ray,
			t_data *data, t_img *frame);
void	draw_column(t_data *data, t_img *frame, t_ray *ray);

//rendering2.c
void	put_pixel(t_img *img, int x, int y, int color);
void	init_texture_position(t_draw_info *info, t_ray *ray, t_data *data);
void	get_texture_addr(t_draw_info *info, t_ray *ray, t_data *data);
void	draw_textured_wall(t_draw_info *info, t_data *data,
			t_img *frame, int x);
void	draw_ceiling_floor(t_draw_info *info, t_data *data,
			t_img *frame, int x);

//textures.c
int		load_textures(t_data *data);

//start_game.c
void	start_game(t_data *data);
void	render_fps(t_data *data);

//render_minimap_and_fps.c
void	put_circle(t_data *data, int cx, int cy, int color);
void	render_minimap(t_data *data);
void	put_square(t_data *data, int x, int y, int color);

void	debug_de_ses_morts(t_data *data);

void	render_frame(t_data *data);
void	put_pixel(t_img *img, int x, int y, int color);
int		render_frame_wrapper(void *param);
void	init_values(int *line_height, int *draw_start,
			int *draw_end, t_ray *ray);

#endif
