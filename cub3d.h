/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:56:44 by rabatist          #+#    #+#             */
/*   Updated: 2025/06/19 18:10:35 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include <stdio.h>
# include <math.h>
# include "mlx/mlx.h"
# include "GNL/get_next_line.h"

# define WIN_WIDTH 2400
# define WIN_HEIGHT 1200
# define PLAYER_SIZE 10
# define COLLISION_RADIUS 0.15

// jai mis l'icone d'une boire pour se qu'il faut free

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

typedef struct s_ray
{
	double		pos_x;		// Starting X position
	double		pos_y;		// Starting Y position
	double		dir_x;		// Ray direction X
	double		dir_y;		// Ray direction Y
	double		delta_x;	// Distance between X grid crossings
	double		delta_y;	// Distance between Y grid crossings
	double		side_x;		// Distance to next X grid line
	double		side_y;		// Distance to next Y grid line
	int			map_x;		// Current map X coordinate
	int			map_y;		// Current map Y coordinate
	int			step_x;		// X step direction (-1 or +1)
	int			step_y;		// Y step direction (-1 or +1)
	int			side;		// Which side was hit (0=X-side, 1=Y-side)
	double		wall_dist;	// Perpendicular distance to wall
}	t_ray;

typedef struct s_keys {
	int			w;							// W key pressed
	int			a;							// A key pressed
	int			s;							// S key pressed
	int			d;							// D key pressed
	int			left;						// Left arrow pressed
	int			right;						// Right arrow pressed
	int			esc;						// Escape key pressed
}	t_keys;

typedef struct s_player
{
	double		pos_x;				// Player X position (map units)
	double		pos_y;				// Player Y position (map units)
	double		dir_x;				// Player direction vector X
	double		dir_y;				// Player direction vector Y
	double		plane_x;			// Camera plane X
	double		plane_y;			// Camera plane Y
	int			player_count;		// Number of players found in map
	char		player;				// Player orientation ('N', 'S', 'E', 'W')
}	t_player;

typedef struct s_map
{
	char		**map;				//📦 2D array of map (final map)
	char		**tmp;				//📦 Temporary map storage (parsing)
	char		**tmp2;				//📦 Temporary map storage (parsing)
	int			floor_color;		// Floor color (int RGB)
	int			ceiling_color;		// Ceiling color (int RGB)
	char		*north_texture;		//📦 Path to north wall texture
	char		*south_texture;		//📦 Path to south wall texture
	char		*west_texture;		//📦 Path to west wall texture
	char		*east_texture;		//📦 Path to east wall texture
	int			heightmap;			// Number of lines in the map
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

typedef struct s_data
{
	void		*mlx;				//📦 MLX instance pointer
	void		*win;				//📦 MLX window pointer
	int			win_width;			// Window width
	int			win_height;			// Window height
	t_map		*map;				//📦 Pointer to map struct
	t_player	*player;			//📦 Pointer to player struct
	t_keys		*keys;				//📦 Pointer to keys struct
	t_textures	textures;
}	t_data;

typedef struct s_img
{
	void	*img;					//📦 MLX image pointer
	char	*addr;					//📦 Image data address
	int		bpp;					// Bits per pixel
	int		line_len;				// Bytes per line
	int		endian;					// Endian-ness
}	t_img;

//parsing_arg.c
int		is_dir(char *str);
int		is_openable(char *str);
int		check_arg(int ac, char **av);

//parsing_map.c
int		parse_map(t_data *data);
void	get_player_pos(t_data *data);
int		parse_the_player(t_data *data);
int		check_map_closed(t_data *data);
int		check_if_only_valid_character(t_data *data);

//parsing_map2.c
int		is_invalid(char c);
int		check_if_xpm(t_data *data);
int		check_if_player_inside(t_data *data);
void	get_player_dir(t_data *data);
void	get_player_dir2(t_data *data);

//parsing_map_color.c
int		check_c_color(t_data *data);
int		check_f_color(t_data *data);
int		check_rgb_format(t_data *data);
int		check_rgb_line(char *line); //new
int		is_valid_rgb(char **str); //new
int		is_str_digit(char *s); //new

//parsing_map_texture.c
int		check_map_texture_and_color(t_data *data);
int		check_no_texture(t_data *data);
int		check_so_texture(t_data *data);
int		check_we_texture(t_data *data);
int		check_ea_texture(t_data *data);

//extract_map_texture_and_color.c
void	extract_map_texture_and_color(t_data *data);
void	extract_map_texture_and_color2(t_data *data);
void	extract_map_texture_and_color3(t_data *data);
int		extract_number(char *str, int *i);
void	parse_color(char *line, int *color); //new

//extract_map.c
void	extract_map(t_data *data);
void	extract_map2(t_data *data, int start);

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

//read_map.c
int		add_line(t_data *data, char *line);
void	read_map(t_data *data, char **av);

//player_movements.c
void	move_player(t_data *data);

//tool.c
int		close_window(t_data *data);
int		handle_keypress(int keycode, t_data *data);
int		handle_keyrelease(int keycode, t_data *data);
void	skip_whitespace(char *str, int *i); //new

//raycasting2.c
void	init_ray_deltas(t_ray *ray);
void	init_ray_side_distances(t_ray *ray);
void	calculate_ray_dir(t_data *data, int x, t_ray *ray);

//raycasting.c
void	DDA(t_data *data, t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
void	init_values(int *lineHeight, int *drawStart, int *drawEnd, t_ray *ray);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_column(t_data *data, int x, t_img *frame, t_ray *ray);

//start_game.c
void	start_game(t_data *data);

void	debug_de_ses_morts(t_data *data);


void	render_frame(t_data *data);
void	put_pixel(t_img *img, int x, int y, int color);
int		render_frame_wrapper(void *param);

#endif
