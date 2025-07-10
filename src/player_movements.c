#include "../cub3d.h"

static int	can_move_x(t_data *data, double new_x, double dx)
{
	double	collision_x;
	int		map_x;
	int		map_y;

	collision_x = COLLISION_RADIUS;
	if (dx < 0)
		collision_x = -collision_x;
	map_x = (int)(new_x + collision_x);
	map_y = (int)data->player->pos_y;
	return (data->map->map[map_y][map_x] != '1');
}

static void	rotate(t_data *data, double angle)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = data->player;
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

static int	can_move_y(t_data *data, double new_y, double dy)
{
	double	collision_y;
	int		map_x;
	int		map_y;

	collision_y = COLLISION_RADIUS;
	if (dy < 0)
		collision_y = -collision_y;
	map_x = (int)data->player->pos_x;
	map_y = (int)(new_y + collision_y);
	return (data->map->map[map_y][map_x] != '1');
}

static void	move(t_data *data, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + dx;
	new_y = data->player->pos_y + dy;
	if (can_move_x(data, new_x, dx))
		data->player->pos_x = new_x;
	if (can_move_y(data, new_y, dy))
		data->player->pos_y = new_y;
}

void	move_player(t_data *data)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.05;
	if (data->keys->esc)
		close_window(data);
	if (data->keys->w)
		move(data, data->player->dir_x * move_speed,
			data->player->dir_y * move_speed);
	if (data->keys->s)
		move(data, -data->player->dir_x * move_speed,
			-data->player->dir_y * move_speed);
	if (data->keys->a)
		move(data, -data->player->plane_x * move_speed,
			-data->player->plane_y * move_speed);
	if (data->keys->d)
		move(data, data->player->plane_x * move_speed,
			data->player->plane_y * move_speed);
	if (data->keys->left)
		rotate(data, -rot_speed);
	if (data->keys->right)
		rotate(data, rot_speed);
}
