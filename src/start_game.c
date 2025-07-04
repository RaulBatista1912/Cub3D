#include "../cub3d.h"
#include <math.h>

void	raycasting(t_data *data, int x, t_img *frame)
{
	t_ray	ray;

	calculate_ray_dir(data, x, &ray);
	init_ray_deltas(&ray);
	init_ray_side_distances(&ray);
	DDA(data, &ray);
	calculate_wall_distance(&ray);//avoid fish eye
	draw_column(data, x, frame, &ray);
}

void render_frame(t_data *data)
{
	t_img	frame;
	int		x;

	frame.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_len, &frame.endian);
	x = 0;
	while (x < WIN_WIDTH)
	{
		raycasting(data, x, &frame);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, frame.img, 0, 0);
	mlx_destroy_image(data->mlx, frame.img);
}

int	simulation_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	move_player(data);
	render_frame(data);
	render_fps(data);
	render_minimap(data);
	return (0);
}

void put_square(t_data *data, int x, int y, int size, int color)
{
    int i = 0;
    int j;

    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_pixel_put(data->mlx, data->win, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void render_minimap(t_data *data)
{
    int	x_start;
    int	y_start;
    int	i;
    int	j;

    x_start = WIN_WIDTH - data->map->widthmap * 10 - 10;
    y_start = WIN_HEIGHT - data->map->heightmap * 10 - 10;
	i = 0;
    while (i < data->map->heightmap)
    {
        j = 0;
        while (j < (int)ft_strlen(data->map->map[i]))
        {
            if (data->map->map[i][j] == '1')
                put_square(data, x_start + j * 10, y_start + i * 10, 10, WHITE);
            else if (ft_strchr("0NSWE", data->map->map[i][j]))
                put_square(data, x_start + j * 10, y_start + i * 10, 10, BLACK);
			j++;
        }
		i++;
    }
    put_square(data, x_start + (int)data->player->pos_x * 10 + 10 / 2 - 2,
                     y_start + (int)data->player->pos_y * 10 + 10 / 2 - 2,
                     5, 0xFF0000);
}


void	render_fps(t_data *data)
{
	struct timeval	tv;
	double			current_time;
	char			*fps_str;

	// Récupération du temps actuel
	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
	data->fps.frames++;

	// Calcul des FPS toutes les secondes
	if (current_time - data->fps.last_time >= 1.0)
	{
		data->fps.fps = data->fps.frames / (current_time - data->fps.last_time);
		data->fps.frames = 0;
		data->fps.last_time = current_time;
	}

	// Conversion des FPS en chaîne de caractères
	fps_str = ft_itoa((int)(data->fps.fps));

	// Affichage des FPS en haut à gauche
	mlx_string_put(data->mlx, data->win, 10, 10, 0x00FF0000, "FPS: ");
	mlx_string_put(data->mlx, data->win, 50, 10, 0x00FF0000, fps_str); // Affiche les FPS

	// Libération de la mémoire
	free(fps_str);
}

void start_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		exit(1);
	}
	if (!load_textures(data))
	{
		ft_putstr_fd("Error\nFailed to load textures\n", 2);
		free_ptr(data);
		exit(1);
    }
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
	{
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		free(data->mlx);
		exit(1);
	}
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);
	mlx_hook(data->win, 3, 1L<<1, handle_keyrelease, data);
	mlx_loop_hook(data->mlx, simulation_loop, data);
	mlx_loop(data->mlx);
}
