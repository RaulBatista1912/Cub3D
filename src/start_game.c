#include "../cub3d.h"
#include <X11/keysym.h>
#include <math.h>

/*
 * RAYCASTING ALGORITHM WITH TEXTURES
 * - Loads textures for north, south, east, west walls
 * - Determines wall orientation using ray side and direction
 * - Maps texture coordinates onto wall stripes
 * - Renders textured walls instead of solid colors
 */

int	close_window(t_data *data)
{
    if (data->textures.north)
        mlx_destroy_image(data->mlx, data->textures.north);
    if (data->textures.south)
        mlx_destroy_image(data->mlx, data->textures.south);
    if (data->textures.west)
        mlx_destroy_image(data->mlx, data->textures.west);
    if (data->textures.east)
        mlx_destroy_image(data->mlx, data->textures.east);
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
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

static void	move_forward(t_data *data, double speed)
{
	t_player	*p = data->player;
	double		newX;
	double		newY;
	double		checkX;
	double		checkY;

	newX = p->pos_x + p->dir_x * speed;
	newY = p->pos_y + p->dir_y * speed;
	if (p->dir_x > 0)
		checkX = newX + COLLISION_RADIUS;
	else
		checkX = newX - COLLISION_RADIUS;
	if (data->map->map[(int)(p->pos_y)][(int)(checkX)] != '1')
		p->pos_x = newX;

	if (p->dir_y > 0)
		checkY = newY + COLLISION_RADIUS;
	else
		checkY = newY - COLLISION_RADIUS;
	if (data->map->map[(int)(checkY)][(int)(p->pos_x)] != '1')
		p->pos_y = newY;
}

static void	move_backward(t_data *data, double speed)
{
	t_player	*p = data->player;
	double		newX = p->pos_x - p->dir_x * speed;
	double		newY = p->pos_y - p->dir_y * speed;
	double		checkX;
	double		checkY;

	if (p->dir_x > 0)
		checkX = newX - COLLISION_RADIUS;
	else
		checkX = newX + COLLISION_RADIUS;
	if (data->map->map[(int)(p->pos_y)][(int)(checkX)] != '1')
		p->pos_x = newX;

	if (p->dir_y > 0)
		checkY = newY - COLLISION_RADIUS;
	else
		checkY = newY + COLLISION_RADIUS;
	if (data->map->map[(int)(checkY)][(int)(p->pos_x)] != '1')
		p->pos_y = newY;
}

static void	strafe_left(t_data *data, double speed)
{
	t_player	*p = data->player;
	double		newX = p->pos_x - p->plane_x * speed;
	double		newY = p->pos_y - p->plane_y * speed;
	double		checkX;
	double		checkY;

	if (p->plane_x > 0)
		checkX = newX - COLLISION_RADIUS;
	else
		checkX = newX + COLLISION_RADIUS;
	if (data->map->map[(int)(p->pos_y)][(int)(checkX)] != '1')
		p->pos_x = newX;

	if (p->plane_y > 0)
		checkY = newY - COLLISION_RADIUS;
	else
		checkY = newY + COLLISION_RADIUS;
	if (data->map->map[(int)(checkY)][(int)(p->pos_x)] != '1')
		p->pos_y = newY;
}

static void	strafe_right(t_data *data, double speed)
{
	t_player	*p = data->player;
	double		newX = p->pos_x + p->plane_x * speed;
	double		newY = p->pos_y + p->plane_y * speed;
	double		checkX;
	double		checkY;

	if (p->plane_x > 0)
		checkX = newX + COLLISION_RADIUS;
	else
		checkX = newX - COLLISION_RADIUS;
	if (data->map->map[(int)(p->pos_y)][(int)(checkX)] != '1')
		p->pos_x = newX;

	if (p->plane_y > 0)
		checkY = newY + COLLISION_RADIUS;
	else
		checkY = newY - COLLISION_RADIUS;
	if (data->map->map[(int)(checkY)][(int)(p->pos_x)] != '1')
		p->pos_y = newY;
}

static void	rotate_left(t_data *data, double rot_speed)
{
    t_player	*p;
    double		oldDirX;
    double		oldPlaneX;

    p = data->player;
    oldDirX = p->dir_x;
    oldPlaneX = p->plane_x;
    p->dir_x = p->dir_x * cos(-rot_speed) - p->dir_y * sin(-rot_speed);
    p->dir_y = oldDirX * sin(-rot_speed) + p->dir_y * cos(-rot_speed);
    p->plane_x = p->plane_x * cos(-rot_speed) - p->plane_y * sin(-rot_speed);
    p->plane_y = oldPlaneX * sin(-rot_speed) + p->plane_y * cos(-rot_speed);
}

static void	rotate_right(t_data *data, double rot_speed)
{
    t_player	*p;
    double		oldDirX;
    double		oldPlaneX;

    p = data->player;
    oldDirX = p->dir_x;
    oldPlaneX = p->plane_x;
    p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
    p->dir_y = oldDirX * sin(rot_speed) + p->dir_y * cos(rot_speed);
    p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
    p->plane_y = oldPlaneX * sin(rot_speed) + p->plane_y * cos(rot_speed);
}

void	move_player(t_data *data)
{
    double	move_speed = 0.05;
    double	rot_speed = 0.05;
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

static void	init_ray_position(t_ray *ray, t_data *data, int x)
{
    double	cameraX = 2.0 * x / WIN_WIDTH - 1;
    ray->pos_x = data->player->pos_x;
    ray->pos_y = data->player->pos_y;
    ray->dir_x = data->player->dir_x + data->player->plane_x * cameraX;
    ray->dir_y = data->player->dir_y + data->player->plane_y * cameraX;
    ray->map_x = (int)ray->pos_x;
    ray->map_y = (int)ray->pos_y;
}

static void	init_ray_deltas(t_ray *ray)
{
    ray->delta_x = fabs(1 / ray->dir_x);
    ray->delta_y = fabs(1 / ray->dir_y);
    if (ray->dir_x < 0)
        ray->step_x = -1;
    else
        ray->step_x = 1;
    if (ray->dir_y < 0)
        ray->step_y = -1;
    else
        ray->step_y = 1;
}

static void	init_ray_side_distances(t_ray *ray)
{
    if (ray->dir_x < 0)
        ray->side_x = (ray->pos_x - ray->map_x) * ray->delta_x;
    else
        ray->side_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;
    if (ray->dir_y < 0)
        ray->side_y = (ray->pos_y - ray->map_y) * ray->delta_y;
    else
        ray->side_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
}

static void	dda_step(t_ray *ray)
{
    if (ray->side_x < ray->side_y)
    {
        ray->side_x += ray->delta_x;
        ray->map_x += ray->step_x;
        ray->side = 0;
    }
    else
    {
        ray->side_y += ray->delta_y;
        ray->map_y += ray->step_y;
        ray->side = 1;
    }
}

static void	perform_dda(t_ray *ray, t_data *data)
{
    int hit = 0;
    while (!hit)
    {
        dda_step(ray);
        if (data->map->map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}

static void	calculate_wall_distance(t_ray *ray)
{
    if (ray->side == 0)
        ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
}

static void	calculate_draw_positions(t_ray *ray, int *drawStart, int *drawEnd, int *lineHeight)
{
    *lineHeight = (int)(WIN_HEIGHT / ray->wall_dist);
    *drawStart = -*lineHeight / 2 + WIN_HEIGHT / 2;
    if (*drawStart < 0)
        *drawStart = 0;
    *drawEnd = *lineHeight / 2 + WIN_HEIGHT / 2;
    if (*drawEnd >= WIN_HEIGHT)
        *drawEnd = WIN_HEIGHT - 1;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
    char	*dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

static void	draw_column(t_img *frame, int x, int drawStart, int drawEnd, t_data *data, void *texture, int texX, int lineHeight)
{
    int		y;
    double	texPos;
    int		texY;
    char	*texture_addr;

    if (texture == data->textures.north)
        texture_addr = data->textures.north_addr;
    else if (texture == data->textures.south)
        texture_addr = data->textures.south_addr;
    else if (texture == data->textures.west)
        texture_addr = data->textures.west_addr;
    else
        texture_addr = data->textures.east_addr;

    y = 0;
    while (y < drawStart)
    {
        put_pixel(frame, x, y, data->map->ceiling_color);
        y++;
    }
    double step = (double)data->textures.height / lineHeight;
    texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;
    while (y <= drawEnd)
    {
        texY = (int)texPos & (data->textures.height - 1); // Assumes texture height is power of 2
        texPos += step;
        int color = *(int *)(texture_addr + (texY * data->textures.line_len + texX * (data->textures.bpp / 8)));
        put_pixel(frame, x, y, color);
        y++;
    }
    while (y < WIN_HEIGHT)
    {
        put_pixel(frame, x, y, data->map->floor_color);
        y++;
    }
}

static void	raycast_column(t_data *data, int x, t_img *frame)
{
    t_ray	ray;
    int		drawStart;
    int		drawEnd;
    int		lineHeight;
    void	*texture;
    double	wallX;
    int		texX;

    init_ray_position(&ray, data, x);
    init_ray_deltas(&ray);
    init_ray_side_distances(&ray);
    perform_dda(&ray, data);
    calculate_wall_distance(&ray);
    calculate_draw_positions(&ray, &drawStart, &drawEnd, &lineHeight);

    // Select texture based on wall orientation
    if (ray.side == 0) // Vertical wall
    {
        if (ray.dir_x > 0)
            texture = data->textures.east;
        else
            texture = data->textures.west;
    }
    else // Horizontal wall
    {
        if (ray.dir_y > 0)
            texture = data->textures.south;
        else
            texture = data->textures.north;
    }

    // Calculate texture x-coordinate
    if (ray.side == 0)
        wallX = ray.pos_y + ray.wall_dist * ray.dir_y;
    else
        wallX = ray.pos_x + ray.wall_dist * ray.dir_x;
    wallX -= floor(wallX);
    texX = (int)(wallX * (double)data->textures.width);
    if (ray.side == 0 && ray.dir_x > 0) texX = data->textures.width - texX - 1; // Flip for east
    if (ray.side == 1 && ray.dir_y < 0) texX = data->textures.width - texX - 1; // Flip for north

    draw_column(frame, x, drawStart, drawEnd, data, texture, texX, lineHeight);
}

void	render_frame(t_data *data)
{
    t_img	frame;
    int		x;

    frame.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
    frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_len, &frame.endian);
    x = 0;
    while (x < WIN_WIDTH)
    {
        raycast_column(data, x, &frame);
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

void	load_textures(t_data *data)
{
    int width, height;
    data->textures.north = mlx_xpm_file_to_image(data->mlx, data->map->north_texture, &width, &height);
    if (!data->textures.north)
    {
        ft_putstr_fd("Error\nFailed to load north texture\n", 2);
        free_exit(data, 1);
    }
    data->textures.width = width;
    data->textures.height = height;
    data->textures.north_addr = mlx_get_data_addr(data->textures.north, &data->textures.bpp, &data->textures.line_len, &data->textures.endian);

    data->textures.south = mlx_xpm_file_to_image(data->mlx, data->map->south_texture, &width, &height);
    if (!data->textures.south || width != data->textures.width || height != data->textures.height)
    {
        ft_putstr_fd("Error\nFailed to load south texture or size mismatch\n", 2);
        free_exit(data, 1);
    }
    data->textures.south_addr = mlx_get_data_addr(data->textures.south, &data->textures.bpp, &data->textures.line_len, &data->textures.endian);

    data->textures.west = mlx_xpm_file_to_image(data->mlx, data->map->west_texture, &width, &height);
    if (!data->textures.west || width != data->textures.width || height != data->textures.height)
    {
        ft_putstr_fd("Error\nFailed to load west texture or size mismatch\n", 2);
        free_exit(data, 1);
    }
    data->textures.west_addr = mlx_get_data_addr(data->textures.west, &data->textures.bpp, &data->textures.line_len, &data->textures.endian);

    data->textures.east = mlx_xpm_file_to_image(data->mlx, data->map->east_texture, &width, &height);
    if (!data->textures.east || width != data->textures.width || height != data->textures.height)
    {
        ft_putstr_fd("Error\nFailed to load east texture or size mismatch\n", 2);
        free_exit(data, 1);
    }
    data->textures.east_addr = mlx_get_data_addr(data->textures.east, &data->textures.bpp, &data->textures.line_len, &data->textures.endian);
}

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
    load_textures(data); // Load textures before rendering
    mlx_hook(data->win, 17, 0, close_window, data);
    mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);
    mlx_hook(data->win, 3, 1L<<1, handle_keyrelease, data);
    mlx_loop_hook(data->mlx, render_frame_wrapper, data);
    mlx_loop(data->mlx);
}
