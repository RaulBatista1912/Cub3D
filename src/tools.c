#include "../cub3d.h"
#include <X11/keysym.h>

/*
	j'ai mis en commentaire car vu que je ne charge pas les textures,
	si je destroy ca va segfault
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
	{
		mlx_destroy_window(data->mlx, data->win);
	}
	printf("Exited the game!\n");
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

void	skip_whitespace(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t'
		|| str[*i] == '\n' || str[*i] == '\r')
		(*i)++;
}
