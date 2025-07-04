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
    *line_height = (int)(WIN_HEIGHT / ray->wall_dist);// c'est la taille du mur sur lecran
    *draw_start = -(*line_height) / 2 + WIN_HEIGHT / 2;//je centre le mur sur lecran
    if (*draw_start < 0)
        *draw_start = 0;
    *draw_end = *line_height / 2 + WIN_HEIGHT / 2;
    if (*draw_end >= WIN_HEIGHT)
        *draw_end = WIN_HEIGHT - 1;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}


//la ya un code mis en commentaire fait de chat, jveux pas lutiliser mais jvais etudier plus tard comment il a fais pour implementer
/*

void draw_column(t_data *data, int x, t_img *frame, t_ray *ray)
{
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     y;
    double  wall_x;
    int     tex_x;
    int     tex_y;
    double  step;
    double  tex_pos;
    int     color;
    char    *texture_addr;

    init_values(&line_height, &draw_start, &draw_end, ray);
    
    // Calculate wall_x (where exactly the wall was hit)
    if (ray->side == 0)
        wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
    else
        wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
    wall_x -= floor(wall_x);  // Only the fractional part
    
    // Calculate tex_x (which x coordinate on the texture)
    tex_x = (int)(wall_x * (double)data->textures.width);
    if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
        tex_x = data->textures.width - tex_x - 1;
    
    // Choose texture based on which wall was hit
    if (ray->side == 0 && ray->dir_x > 0)
        texture_addr = data->textures.east_addr;  // East wall
    else if (ray->side == 0 && ray->dir_x < 0)
        texture_addr = data->textures.west_addr;  // West wall
    else if (ray->side == 1 && ray->dir_y > 0)
        texture_addr = data->textures.south_addr; // South wall
    else
        texture_addr = data->textures.north_addr; // North wall
    
    // Calculate texture step and starting position
    step = 1.0 * data->textures.height / line_height;
    tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
    
    // Draw vertical line with texture
    y = draw_start;
    while (y <= draw_end)
    {
        tex_y = (int)tex_pos & (data->textures.height - 1);
        tex_pos += step;
        
        // Get color from texture
        color = *(unsigned int*)(texture_addr + 
                                (tex_y * data->textures.line_len + 
                                 tex_x * (data->textures.bpp / 8)));
        
        put_pixel(frame, x, y, color);
        y++;
    }

    // Draw ceiling and floor
    y = 0;
    while (y < draw_start)
        put_pixel(frame, x, y++, data->map->ceiling_color);
    
    y = draw_end + 1;
    while (y < WIN_HEIGHT)
        put_pixel(frame, x, y++, data->map->floor_color);
}

*/

void	init_texture_position(t_draw_info *info, t_ray *ray, t_data *data)
{
    if (ray->side == 0)
        info->wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
    else
        info->wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
    info->wall_x -= floor(info->wall_x);
    info->tex_x = (int)(info->wall_x * (double)data->textures.width);
    if ((ray->side == 0 && ray->dir_x > 0) || 
        (ray->side == 1 && ray->dir_y < 0))
        info->tex_x = data->textures.width - info->tex_x - 1;
}

void	get_texture_addr(t_draw_info *info, t_ray *ray, t_data *data)
{
    if (ray->side == 0 && ray->dir_x > 0)
        info->texture_addr = data->textures.east_addr;
    else if (ray->side == 0 && ray->dir_x < 0)
        info->texture_addr = data->textures.west_addr;
    else if (ray->side == 1 && ray->dir_y > 0)
        info->texture_addr = data->textures.south_addr;
    else
        info->texture_addr = data->textures.north_addr;
	}

void	draw_textured_wall(t_draw_info *info, t_data *data, 
                        t_img *frame, int x)
{
    info->step = 1.0 * data->textures.height / info->line_height;
    info->tex_pos = (info->draw_start - WIN_HEIGHT / 2 + 
                    info->line_height / 2) * info->step;
    info->y = info->draw_start;
    while (info->y <= info->draw_end)
    {
        info->tex_y = (int)info->tex_pos & (data->textures.height - 1);
        info->tex_pos += info->step;
        info->color = *(unsigned int*)(info->texture_addr + 
                (info->tex_y * data->textures.line_len + 
                info->tex_x * (data->textures.bpp / 8)));
        put_pixel(frame, x, info->y, info->color);
        info->y++;
    }
}

void	draw_ceiling_floor(t_draw_info *info, t_data *data, 
	t_img *frame, int x)
	{
		info->y = 0;
		while (info->y < info->draw_start)
        put_pixel(frame, x, info->y++, data->map->ceiling_color);
		info->y = info->draw_end + 1;
		while (info->y < WIN_HEIGHT)
        put_pixel(frame, x, info->y++, data->map->floor_color);
	}
	
void	textures_handle(t_draw_info *info, t_ray *ray, t_data *data, t_img *frame, int x)
{
	init_values(&info->line_height, &info->draw_start, &info->draw_end, ray);
	init_texture_position(info, ray, data);
	get_texture_addr(info, ray, data);
	draw_textured_wall(info, data, frame, x);
	draw_ceiling_floor(info, data, frame, x);
}

// le premier while c'est pour dessiner le mur de drawend de drawstart a drawend
//le deuxieme while c'est pour dessiner le plafond de 0 a drawstart
//le troixieme while c'est pour dessiner le sol de drawend+1 a winheight
void	draw_column(t_data *data, int x, t_img *frame, t_ray *ray)
{
	/* int			lineHeight;
	int			drawStart;
	int			drawEnd; */
	int			y;
	t_draw_info	info;

	//init_values(&lineHeight, &drawStart, &drawEnd, ray);
	/* y = info.draw_start;
	while (y <= info.draw_end)
	{
		put_pixel(frame, x, y, 0x00FF0000);
		y++;
	} */
	textures_handle(&info, ray, data, frame, x);

	// Plafond et sol avec les couleurs de la carte
	y = 0;
	//on commence au pixel 0 en haut de lecran, on continue jusqua drawstart
	while (y < info.draw_start)
		put_pixel(frame, x, y++, data->map->ceiling_color); // dessiner le plafond
	y = info.draw_end + 1;
	//on colories jusqua winheight mais depuis le end du mur
	while (y < WIN_HEIGHT)
		put_pixel(frame, x, y++, data->map->floor_color); // dessiner le sol
}
