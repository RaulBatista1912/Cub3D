#include "../cub3d.h"

void	DDA(t_data *data, t_ray *ray)
{
	int	hit; // Indicateur de collision avec un mur

	hit = 0;
	while (!hit)
	{
		//avancer au prochain bord le plus proche
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // Mur vertical touché
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // Mur horizontal touché
		}

		// Vérifier si on a touché un mur
		if (data->map->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0) // Mur vertical
		ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2.0) / ray->dir_x;
	else // Mur horizontal
		ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2.0) / ray->dir_y;
}

// calcule la taille de lecran diviser par la distance jusquau mur pour avoir la taille du mur
/*
Écran (600px de haut)
┌─────────────────┐ ← 0
│     PLAFOND     │
│                 │
├─────────────────┤ ← drawStart
│                 │
│      MUR        │ ← Centre (300)
│                 │
├─────────────────┤ ← drawEnd
│                 │
│      SOL        │
└─────────────────┘ ← 600
*/
// 58 - 62 jsp la c chat qui ma mis ca pour des "protection"
void	init_values(int *lineHeight, int *drawStart, int *drawEnd, t_ray *ray)
{
	*lineHeight = (int)(WIN_HEIGHT / ray->wall_dist);
	*drawStart = -(*lineHeight) / 2 + WIN_HEIGHT / 2;
	if (*drawStart < 0)
		*drawStart = 0;
	*drawEnd = *lineHeight / 2 + WIN_HEIGHT / 2;
	if (*drawEnd >= WIN_HEIGHT)
		*drawEnd = WIN_HEIGHT - 1;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// le premier while c'est pour dessiner le mur de drawend de drawstart a drawend
//le deuxieme while c'est pour dessiner le plafond de 0 a drawstart
//le troixieme while c'est pour dessiner le sol de drawend+1 a winheight
void	draw_column(t_data *data, int x, t_img *frame, t_ray *ray)
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int	y;

	init_values(&lineHeight, &drawStart, &drawEnd, ray);
	y = drawStart;
	while (y <= drawEnd)
	{
		put_pixel(frame, x, y, 0x00FF0000);
		y++;
	}

	// Plafond et sol avec les couleurs de la carte
	y = 0;
	while (y < drawStart)
		put_pixel(frame, x, y++, data->map->ceiling_color); // Utiliser ceiling_color
	y = drawEnd + 1;
	while (y < WIN_HEIGHT)
		put_pixel(frame, x, y++, data->map->floor_color); // Utiliser floor_color
}
