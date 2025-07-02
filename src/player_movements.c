#include "../cub3d.h"


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

void move_player(t_data *data)
{
    double  move_speed;
    double  rot_speed;

    move_speed = 0.05;
    rot_speed = 0.05;
    if (data->keys->esc)
    {
        close_window(data);
    }
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
