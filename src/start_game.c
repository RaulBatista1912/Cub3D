#include "../cub3d.h"
#include <X11/keysym.h>
#include <math.h>

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

static int can_move_x(t_data *data, double newX, double dx)
{
    double collisionX;
    int mapX;
    int mapY;

    collisionX = COLLISION_RADIUS;
    if (dx < 0)
        collisionX = -collisionX;
    mapX = (int)(newX + collisionX);
    mapY = (int)data->player->pos_y;
    return data->map->map[mapY][mapX] != '1';
}

static int can_move_y(t_data *data, double newY, double dy)
{
    double collisionY;
    int mapX;
    int mapY;

    collisionY = COLLISION_RADIUS;
    if (dy < 0)
        collisionY = -collisionY;
    mapX = (int)data->player->pos_x;
    mapY = (int)(newY + collisionY);
    return data->map->map[mapY][mapX] != '1';
}

static void move(t_data *data, double dx, double dy)
{
    double newX;
    double newY;

    newX = data->player->pos_x + dx;
    newY = data->player->pos_y + dy;
    if (can_move_x(data, newX, dx))
        data->player->pos_x = newX;
    if (can_move_y(data, newY, dy))
        data->player->pos_y = newY;
}

static void rotate(t_data *data, double angle)
{
    t_player *p;
    double oldDirX;
    double oldPlaneX;

    p = data->player;
    oldDirX = p->dir_x;
    p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
    p->dir_y = oldDirX * sin(angle) + p->dir_y * cos(angle);
    oldPlaneX = p->plane_x;
    p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
    p->plane_y = oldPlaneX * sin(angle) + p->plane_y * cos(angle);
}

void move_player(t_data *data)
{
    double move_speed;
    double rot_speed;

    move_speed = 0.05;
    rot_speed = 0.05;
    if (data->keys->esc)
        close_window(data);
    if (data->keys->w)
        move(data, data->player->dir_x * move_speed, data->player->dir_y * move_speed);
    if (data->keys->s)
        move(data, -data->player->dir_x * move_speed, -data->player->dir_y * move_speed);
    if (data->keys->a)
        move(data, -data->player->plane_x * move_speed, -data->player->plane_y * move_speed);
    if (data->keys->d)
        move(data, data->player->plane_x * move_speed, data->player->plane_y * move_speed);
    if (data->keys->left)
        rotate(data, -rot_speed);
    if (data->keys->right)
        rotate(data, rot_speed);
}

static void init_ray_position(t_ray *ray, t_data *data, int x)
{
    double cameraX;

    cameraX = 2.0 * x / WIN_WIDTH - 1;
    ray->pos_x = data->player->pos_x;
    ray->pos_y = data->player->pos_y;
    ray->dir_x = data->player->dir_x + data->player->plane_x * cameraX;
    ray->dir_y = data->player->dir_y + data->player->plane_y * cameraX;
    ray->map_x = (int)ray->pos_x;
    ray->map_y = (int)ray->pos_y;
}

static void init_ray_deltas(t_ray *ray)
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

static void init_ray_side_distances(t_ray *ray)
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

static void dda_step(t_ray *ray)
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

static void perform_dda(t_ray *ray, t_data *data)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        dda_step(ray);
        if (data->map->map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}

static void calculate_wall_distance(t_ray *ray)
{
    if (ray->side == 0)
        ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
}

static void calculate_draw_positions(t_ray *ray, int *drawStart, int *drawEnd, int *lineHeight)
{
    *lineHeight = (int)(WIN_HEIGHT / ray->wall_dist);
    *drawStart = -*lineHeight / 2 + WIN_HEIGHT / 2;
    if (*drawStart < 0)
        *drawStart = 0;
    *drawEnd = *lineHeight / 2 + WIN_HEIGHT / 2;
    if (*drawEnd >= WIN_HEIGHT)
        *drawEnd = WIN_HEIGHT - 1;
}

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

static int lerp_color(int c1, int c2, double t)
{
    int r;
    int g;
    int b;

    r = (int)(((c1 >> 16) & 0xFF) + (((c2 >> 16) & 0xFF) - ((c1 >> 16) & 0xFF)) * t);
    g = (int)(((c1 >> 8) & 0xFF) + (((c2 >> 8) & 0xFF) - ((c1 >> 8) & 0xFF)) * t);
    b = (int)((c1 & 0xFF) + ((c2 & 0xFF) - (c1 & 0xFF)) * t);
    return (r << 16) | (g << 8) | b;
}

static void draw_ceiling(t_img *frame, int x, int drawStart, t_data *data,
        int center, int center_color, int grad_size)
{
    int y;
    int color;

    y = 0;
    while (y < drawStart)
    {
        if (y >= center - grad_size && y < center)
            color = lerp_color(data->map->ceiling_color, center_color, (double)(y - (center - grad_size)) / grad_size);
        else if (y < center - grad_size)
            color = data->map->ceiling_color;
        else
            color = center_color;
        put_pixel(frame, x, y, color);
        y++;
    }
}

static int get_texture_color(char *texture_addr, int texX, int texY, t_textures *textures)
{
    return *(int *)(texture_addr + (texY * textures->line_len + texX * (textures->bpp / 8)));
}

static void draw_wall(t_img *frame, int x, int drawStart, int drawEnd,
        t_data *data, char *texture_addr, int texX, int lineHeight)
{
    int y;
    double step;
    double texPos;
    int color;

    step = (double)data->textures.height / lineHeight;
    texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;
    y = drawStart;
    while (y <= drawEnd)
    {
        color = get_texture_color(texture_addr, texX, (int)texPos & (data->textures.height - 1), &data->textures);
        put_pixel(frame, x, y, color);
        texPos += step;
        y++;
    }
}

static void draw_floor(t_img *frame, int x, int drawEnd, t_data *data,
        int center, int center_color, int grad_size)
{
    int y;
    int color;

    y = drawEnd + 1;
    while (y < WIN_HEIGHT)
    {
        if (y >= center && y < center + grad_size)
            color = lerp_color(center_color, data->map->floor_color, (double)(y - center) / grad_size);
        else if (y >= center + grad_size)
            color = data->map->floor_color;
        else
            color = center_color;
        put_pixel(frame, x, y, color);
        y++;
    }
}

static void draw_column(t_img *frame, int x, int drawStart, int drawEnd,
        t_data *data, void *texture, int texX, int lineHeight)
{
    char *texture_addr;
    int center;
    int center_color;
    int grad_size;

    center = WIN_HEIGHT / 2;
    center_color = lerp_color(data->map->ceiling_color, data->map->floor_color, 0.5);
    grad_size = WIN_HEIGHT / 8;
    if (texture == data->textures.north)
        texture_addr = data->textures.north_addr;
    else if (texture == data->textures.south)
        texture_addr = data->textures.south_addr;
    else if (texture == data->textures.west)
        texture_addr = data->textures.west_addr;
    else
        texture_addr = data->textures.east_addr;
    draw_ceiling(frame, x, drawStart, data, center, center_color, grad_size);
    draw_wall(frame, x, drawStart, drawEnd, data, texture_addr, texX, lineHeight);
    draw_floor(frame, x, drawEnd, data, center, center_color, grad_size);
}

static void perform_raycast(t_ray *ray, t_data *data, int x)
{
    init_ray_position(ray, data, x);
    init_ray_deltas(ray);
    init_ray_side_distances(ray);
    perform_dda(ray, data);
    calculate_wall_distance(ray);
}

static void *select_texture(t_ray *ray, t_data *data)
{
    if (ray->side == 0)
    {
        if (ray->dir_x > 0)
            return data->textures.east;
        return data->textures.west;
    }
    if (ray->dir_y > 0)
        return data->textures.south;
    return data->textures.north;
}

static int calculate_texX(t_ray *ray, t_data *data)
{
    double wallX;
    int texX;

    if (ray->side == 0)
        wallX = ray->pos_y + ray->wall_dist * ray->dir_y;
    else
        wallX = ray->pos_x + ray->wall_dist * ray->dir_x;
    wallX -= floor(wallX);
    texX = (int)(wallX * (double)data->textures.width);
    if (ray->side == 0 && ray->dir_x > 0)
        texX = data->textures.width - texX - 1;
    if (ray->side == 1 && ray->dir_y < 0)
        texX = data->textures.width - texX - 1;
    return texX;
}

static void raycast_column(t_data *data, int x, t_img *frame)
{
    t_ray ray;
    int drawStart;
    int drawEnd;
    int lineHeight;

    perform_raycast(&ray, data, x);
    calculate_draw_positions(&ray, &drawStart, &drawEnd, &lineHeight);
    draw_column(frame, x, drawStart, drawEnd, data, select_texture(&ray, data), calculate_texX(&ray, data), lineHeight);
}

void render_frame(t_data *data)
{
    t_img frame;
    int x;

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

int render_frame_wrapper(void *param)
{
    t_data *data;

    data = (t_data *)param;
    move_player(data);
    render_frame(data);
    return (0);
}

static void load_texture(t_data *data, void **texture, char **texture_addr, char *path, int *width, int *height)
{
    *texture = mlx_xpm_file_to_image(data->mlx, path, width, height);
    if (!*texture)
    {
        ft_putstr_fd("Error\nFailed to load texture: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd("\n", 2);
        free_exit(data, 1);
    }
    *texture_addr = mlx_get_data_addr(*texture, &data->textures.bpp, &data->textures.line_len, &data->textures.endian);
}

void load_textures(t_data *data)
{
    int width;
    int height;

    load_texture(data, &data->textures.north, &data->textures.north_addr, data->map->north_texture, &width, &height);
    data->textures.width = width;
    data->textures.height = height;
    load_texture(data, &data->textures.south, &data->textures.south_addr, data->map->south_texture, &width, &height);
    if (width != data->textures.width || height != data->textures.height)
    {
        ft_putstr_fd("Error\nTexture size mismatch for south texture\n", 2);
        free_exit(data, 1);
    }
    load_texture(data, &data->textures.west, &data->textures.west_addr, data->map->west_texture, &width, &height);
    if (width != data->textures.width || height != data->textures.height)
    {
        ft_putstr_fd("Error\nTexture size mismatch for west texture\n", 2);
        free_exit(data, 1);
    }
    load_texture(data, &data->textures.east, &data->textures.east_addr, data->map->east_texture, &width, &height);
    if (width != data->textures.width || height != data->textures.height)
    {
        ft_putstr_fd("Error\nTexture size mismatch for east texture\n", 2);
        free_exit(data, 1);
    }
}

void start_game(t_data *data)
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
    load_textures(data);
    mlx_hook(data->win, 17, 0, close_window, data);
    mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);
    mlx_hook(data->win, 3, 1L<<1, handle_keyrelease, data);
    mlx_loop_hook(data->mlx, render_frame_wrapper, data);
    mlx_loop(data->mlx);
}
