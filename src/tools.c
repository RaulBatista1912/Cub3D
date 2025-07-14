/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:29:12 by isaiah            #+#    #+#             */
/*   Updated: 2025/07/14 17:45:57 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	printf("Exited the game!\n");
	exit(0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 65307)
		data->keys->esc = 1;
	else if (keycode == 119)
		data->keys->w = 1;
	else if (keycode == 115)
		data->keys->s = 1;
	else if (keycode == 97)
		data->keys->a = 1;
	else if (keycode == 100)
		data->keys->d = 1;
	else if (keycode == 65361)
		data->keys->left = 1;
	else if (keycode == 65363)
		data->keys->right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == 65307)
		data->keys->esc = 0;
	else if (keycode == 119)
		data->keys->w = 0;
	else if (keycode == 115)
		data->keys->s = 0;
	else if (keycode == 97)
		data->keys->a = 0;
	else if (keycode == 100)
		data->keys->d = 0;
	else if (keycode == 65361)
		data->keys->left = 0;
	else if (keycode == 65363)
		data->keys->right = 0;
	return (0);
}

void	skip_whitespace(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t'
		|| str[*i] == '\n' || str[*i] == '\r')
		(*i)++;
}

int	is_str_digit(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
