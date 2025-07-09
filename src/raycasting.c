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
	*line_height = (int)(WIN_HEIGHT / ray->wall_dist);

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

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
 on sait ou le rayon est dans la map mais on veut savoir ou exactement dans
 la case il a toucher

side est a 0 si le rayon touche un mur NORD SUD et a 1 si il touche EST OUEST
*/
void	init_texture_position(t_draw_info *info, t_ray *ray, t_data *data)
{

	//position_départ + distance * direction = position exact en x dans la case
	/*
	Exemple avec des chiffres:
	- ray->pos_y = 2.3 (position de depart)
	- ray->wall_dist = 1.8 (distance parcourue)  
	- ray->dir_y = 1.0 (direction vers le sud)
	Resultat: wall_x = 2.3 + 1.8 * 1.0 = 4.1
	Apres floor(): wall_x = 4.1 - 4.0 = 0.1 (10% dans la case)
	*/
	if (ray->side == 0)
		info->wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		info->wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;

	// on prend just le chiffre apres la virgule
	info->wall_x -= floor(info->wall_x);


	// 0.6 * 64 = 38
	// en gros calculer quelle colonne a gerer
	info->tex_x = (int)(info->wall_x * (double)data->textures.width);
	
	/*
	c'est pour pas que les images soient inverser, ca fix
	*/
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
	/*
	step c'est combien de distance il va parcourir dans la texture par loop
	mur : 200px
	64 / 200 = 0.32px 

	il va se deplacer de 0.32 a chaque loop en Y
	*/
	info->step = 1.0 * data->textures.height / info->line_height;
	info->tex_pos = (info->draw_start - WIN_HEIGHT / 2 + 
					info->line_height / 2) * info->step;
	info->y = info->draw_start;
	while (info->y <= info->draw_end)
	{
		/*
		info->y = pixel a l'ecran (300, 301, 302...)
		tex_pos = position dans la texture (0.0, 0.32, 0.64, 0.96, 1.28...)
		tex_y = ligne de texture a utiliser (0, 0, 0, 0, 1...)
		on garde le chiffre arriere la virgule
		Plusieurs pixels d'ecran utilisent la meme ligne de texture = etirement
		
		info->y prend draw_start et s'incremente a chaque fois
		a chaque loop on incremente aussi tex_pos de 0.32 (step)
		si tex_pos depasse un chiffre entier on passe au prochain pixel de la texture
		*/
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
	int			y;
	t_draw_info	info;

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
