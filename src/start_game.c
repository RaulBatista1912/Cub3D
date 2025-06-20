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

int simulation_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	move_player(data);
	render_frame(data);
	return (0);
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
