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
void	init_values(int *line_height, int *draw_start, int *draw_end, t_ray *ray)
{
	//calculate the height of the wall
	*line_height = (int)(WIN_HEIGHT / ray->wall_dist * 0.8);

	/*
	* calculates where the wall is starting

	- if your wall is 200px and your screen size it 800px, you want the wall to be
	between 300 - 500.
	- to do so you will get the center - 100, you get 300.
	{ -200 / 2 = -100 | -100 + 800 / 2 = 300 }

	*/
	*draw_start = -(*line_height) / 2 + WIN_HEIGHT / 2;

	// if the wall is too big it will be a negatif number, if it is i set it to 0
	if (*draw_start < 0)
		*draw_start = 0;

	// finding the end of the wall, same as before
	*draw_end = *line_height / 2 + WIN_HEIGHT / 2;

	// if it passes the limits of the screen i set the limit to 799
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}