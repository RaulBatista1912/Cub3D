#include "../cub3d.h"

// casting a ray for each vertical rows of pixels in window screen, and applying a slight curve on it
void	calculate_ray_dir(t_data *data, int x, t_ray *ray)
{
	double	cameraX;

	cameraX = 2.0 * x / WIN_WIDTH - 1.0;

	// je mes la position du rayon en tant que la pos du joueru
	ray->pos_x = data->player->pos_x;
	ray->pos_y = data->player->pos_y;

	//
	ray->dir_x = data->player->dir_x + data->player->plane_x * cameraX;
	ray->dir_y = data->player->dir_y + data->player->plane_y * cameraX;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
}

//pour calculer la distance jusqua la case da coter
//si c'est a droite je prend le chiffre a droite - ma pos
//si c'est a gauche je prend moi - le chiffre a gauche
//exemple en X:
//	moi = 2.3
//	droite = 3.0
//	gauche = 2.0
//		3.0 - 2.3 = 0.7 | 2.3 - 2.0 = 0.3
// soit (2.3 - 2) * 1.42 = 0.3 * 1.42 = 0.426 | 2.3 Player pos, 2.0 map grid pos = 0.3 X distance, deltax = 1.42 so 0.3 * 1.42 = 0.426 to travel to next real grid to left.
// tu fais la position actuel jusqua la prochaine gros genre 0.426 + deltax cava donner a chaque fois les interception a la prochaine ligne
void	init_ray_side_distances(t_ray *ray)
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

// deltax et deltay vont maider a trouver
// ou seront les ligne X Y dans la map
// "en gros c just pour aider a trouver ou je vais avoir les lignes dans mon trait de rayons, si je sais que chaque 10 mettre en Y je fais 1m de X, ca maide a trouver les autres ligne"
//	deltax c'est comme si a nimporte ou je suis il cree une case imaginaire a pile uniter de moi et ca calcule la distance jusqua la
void	init_ray_deltas(t_ray *ray)
{
	//fabs car je veux la valeur en positif
	ray->delta_x = fabs(1.0 / ray->dir_x);
	ray->delta_y = fabs(1.0 / ray->dir_y);

	//c'est un indiquateur pour dire aux rayons ou avancer
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}
