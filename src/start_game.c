#include "../cub3d.h"
#include <X11/keysym.h>
#include <math.h>

// --- Window and Key Handling ---

int	close_window(t_data *data)
{
	free(data->mlx);
	exit(0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		data->keys->esc = 1;
	else if (keycode == XK_w)
		data->keys->w = 1;
	else if (keycode == XK_s)
		data->keys->s = 1;
	else if (keycode == XK_a)
		data->keys->a = 1;
	else if (keycode == XK_d)
		data->keys->d = 1;
	else if (keycode == XK_Left)
		data->keys->left = 1;
	else if (keycode == XK_Right)
		data->keys->right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		data->keys->esc = 0;
	else if (keycode == XK_w)
		data->keys->w = 0;
	else if (keycode == XK_s)
		data->keys->s = 0;
	else if (keycode == XK_a)
		data->keys->a = 0;
	else if (keycode == XK_d)
		data->keys->d = 0;
	else if (keycode == XK_Left)
		data->keys->left = 0;
	else if (keycode == XK_Right)
		data->keys->right = 0;
	return (0);
}

// --- Player Movement Helpers ---

static void	move_forward(t_data *data, double speed)
{
	t_player *p = data->player;
	double newX = p->pos_x + p->dir_x * speed;
	double newY = p->pos_y + p->dir_y * speed;
	if (data->map->map[(int)newY][(int)p->pos_x] != '1')
		p->pos_y = newY;
	if (data->map->map[(int)p->pos_y][(int)newX] != '1')
		p->pos_x = newX;
}

static void	move_backward(t_data *data, double speed)
{
	t_player *p = data->player;
	double newX = p->pos_x - p->dir_x * speed;
	double newY = p->pos_y - p->dir_y * speed;
	if (data->map->map[(int)newY][(int)p->pos_x] != '1')
		p->pos_y = newY;
	if (data->map->map[(int)p->pos_y][(int)newX] != '1')
		p->pos_x = newX;
}

static void	strafe_left(t_data *data, double speed)
{
	t_player *p = data->player;
	double newX = p->pos_x - p->plane_x * speed;
	double newY = p->pos_y - p->plane_y * speed;
	if (data->map->map[(int)newY][(int)p->pos_x] != '1')
		p->pos_y = newY;
	if (data->map->map[(int)p->pos_y][(int)newX] != '1')
		p->pos_x = newX;
}

static void	strafe_right(t_data *data, double speed)
{
	t_player *p = data->player;
	double newX = p->pos_x + p->plane_x * speed;
	double newY = p->pos_y + p->plane_y * speed;
	if (data->map->map[(int)newY][(int)p->pos_x] != '1')
		p->pos_y = newY;
	if (data->map->map[(int)p->pos_y][(int)newX] != '1')
		p->pos_x = newX;
}

static void	rotate_left(t_data *data, double rot_speed)
{
	t_player *p = data->player;
	double oldDirX = p->dir_x;
	double oldPlaneX = p->plane_x;
	p->dir_x = p->dir_x * cos(-rot_speed) - p->dir_y * sin(-rot_speed);
	p->dir_y = oldDirX * sin(-rot_speed) + p->dir_y * cos(-rot_speed);
	p->plane_x = p->plane_x * cos(-rot_speed) - p->plane_y * sin(-rot_speed);
	p->plane_y = oldPlaneX * sin(-rot_speed) + p->plane_y * cos(-rot_speed);
}

static void	rotate_right(t_data *data, double rot_speed)
{
	t_player *p = data->player;
	double oldDirX = p->dir_x;
	double oldPlaneX = p->plane_x;
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = oldDirX * sin(rot_speed) + p->dir_y * cos(rot_speed);
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = oldPlaneX * sin(rot_speed) + p->plane_y * cos(rot_speed);
}

// --- Main Movement Dispatcher ---

void	move_player(t_data *data)
{
	double move_speed = 0.05;
	double rot_speed = 0.03;

	if (data->keys->esc)
		close_window(data);
	if (data->keys->w)
		move_forward(data, move_speed);
	if (data->keys->s)
		move_backward(data, move_speed);
	if (data->keys->a)
		strafe_left(data, move_speed);
	if (data->keys->d)
		strafe_right(data, move_speed);
	if (data->keys->left)
		rotate_left(data, rot_speed);
	if (data->keys->right)
		rotate_right(data, rot_speed);
}

// --- Rendering Helpers ---

void	put_pixel(t_img *img, int x, int y, int color)
{
	char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// Draws a single vertical stripe (column) of the wall, ceiling, and floor
static void	draw_column(t_img *frame, int x, int drawStart, int drawEnd, t_data *data)
{
	int y = 0;
	while (y < drawStart)
		put_pixel(frame, x, y++, data->map->ceiling_color);
	while (y < drawEnd)
		put_pixel(frame, x, y++, 0xAAAAAA);
	while (y < WIN_HEIGHT)
		put_pixel(frame, x, y++, data->map->floor_color);
}

// Raycasting for a single column, returns wall hit info and draw positions
static void	raycast_column(t_data *data, int x, int *drawStart, int *drawEnd)
{
	double posX = data->player->pos_x;
	double posY = data->player->pos_y;
	double dirX = data->player->dir_x;
	double dirY = data->player->dir_y;
	double planeX = data->player->plane_x;
	double planeY = data->player->plane_y;
	double cameraX = 2.0 * x / WIN_WIDTH - 1;
	double rayDirX = dirX + planeX * cameraX;
	double rayDirY = dirY + planeY * cameraX;
	int mapX = (int)posX;
	int mapY = (int)posY;
	double deltaDistX = fabs(1 / rayDirX);
	double deltaDistY = fabs(1 / rayDirY);
	int stepX = (rayDirX < 0) ? -1 : 1;
	int stepY = (rayDirY < 0) ? -1 : 1;
	double sideDistX = (rayDirX < 0) ? (posX - mapX) * deltaDistX : (mapX + 1.0 - posX) * deltaDistX;
	double sideDistY = (rayDirY < 0) ? (posY - mapY) * deltaDistY : (mapY + 1.0 - posY) * deltaDistY;
	int hit = 0, side;
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (data->map->map[mapY][mapX] == '1')
			hit = 1;
	}
	double perpWallDist = (side == 0)
		? (mapX - posX + (1 - stepX) / 2) / rayDirX
		: (mapY - posY + (1 - stepY) / 2) / rayDirY;
	int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
	*drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (*drawStart < 0) *drawStart = 0;
	*drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (*drawEnd >= WIN_HEIGHT) *drawEnd = WIN_HEIGHT - 1;
}

// --- Main Render Loop ---

void	render_frame(t_data *data)
{
	t_img	frame;
	int		x, drawStart, drawEnd;

	frame.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_len, &frame.endian);
	x = 0;
	while (x < WIN_WIDTH)
	{
		raycast_column(data, x, &drawStart, &drawEnd);
		draw_column(&frame, x, drawStart, drawEnd, data);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, frame.img, 0, 0);
	mlx_destroy_image(data->mlx, frame.img);
}

int	render_frame_wrapper(void *param)
{
	t_data *data = (t_data *)param;
	move_player(data);
	render_frame(data);
	return (0);
}

// --- Initialization ---

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->esc = 0;
}

// --- Game Entry Point ---

void	start_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		exit(1);
	}
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
	{
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		free(data->mlx);
		exit(1);
	}
	data->keys = malloc(sizeof(t_keys));
	if (!data->keys)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		free(data->mlx);
		exit(1);
	}
	init_keys(data->keys);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);
	mlx_hook(data->win, 3, 1L<<1, handle_keyrelease, data);
	mlx_loop_hook(data->mlx, render_frame_wrapper, data);
	mlx_loop(data->mlx);
}
