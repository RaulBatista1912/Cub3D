#include "../cub3d.h"

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

void	draw_column(t_data *data, int x, t_img *frame, t_ray *ray)
{
	t_draw_info	info;

	textures_handle(&info, ray, data, frame, x);
}
