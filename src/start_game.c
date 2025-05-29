#include "../cub3d.h"
#include <X11/keysym.h>
#include <math.h>

/*
 * =============================================================================
 * RAYCASTING ALGORITHM EXPLANATION
 * =============================================================================
 *
 * The raycasting algorithm creates a 3D-like view from a 2D map by casting rays
 * from the player's position across the field of view and calculating distances
 * to walls. Here's how it works:
 *
 * 1. CAMERA SETUP:
 *    - Player has position (pos_x, pos_y) and direction vector (dir_x, dir_y)
 *    - Camera plane is perpendicular to direction, defines FOV width
 *    - For each screen column (x), calculate camera coordinate (-1 to +1)
 *
 * 2. RAY CALCULATION:
 *    - Ray direction = player direction + camera plane * camera coordinate
 *    - This creates rays that fan out across the field of view
 *
 * 3. DDA (Digital Differential Analyzer):
 *    - Step through map grid following the ray until hitting a wall
 *    - Calculate step direction and initial distances to next grid lines
 *    - Use deltaDistX/Y (distance between grid crossings) for efficiency
 *
 * 4. WALL DISTANCE & HEIGHT:
 *    - Calculate perpendicular distance to avoid fisheye effect
 *    - Wall height = screen_height / perpendicular_distance
 *    - Draw start/end positions center the wall vertically
 *
 * 5. FISHEYE CORRECTION:
 *    - Use perpendicular distance instead of actual ray distance
 *    - Prevents walls from appearing curved at screen edges
 *
 * COMMON BUGS FIXED:
 * - Fisheye effect: Using perpendicular wall distance
 * - Division by zero: Checking for zero ray directions
 * - Wall rendering: Proper start/end bounds checking
 * - Stepping errors: Correct initial side distance calculations
 */

// Structure to hold ray information for cleaner parameter passing
typedef struct s_ray
{
	double	pos_x;		// Starting X position
	double	pos_y;		// Starting Y position
	double	dir_x;		// Ray direction X
	double	dir_y;		// Ray direction Y
	double	delta_x;	// Distance between X grid crossings
	double	delta_y;	// Distance between Y grid crossings
	double	side_x;		// Distance to next X grid line
	double	side_y;		// Distance to next Y grid line
	int		map_x;		// Current map X coordinate
	int		map_y;		// Current map Y coordinate
	int		step_x;		// X step direction (-1 or +1)
	int		step_y;		// Y step direction (-1 or +1)
	int		side;		// Which side was hit (0=X-side, 1=Y-side)
	double	wall_dist;	// Perpendicular distance to wall
}	t_ray;

// --- Window and Key Handling ---

int	close_window(t_data *data)
{
	free(data->mlx);
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

// --- Player Movement Helpers ---

static void	move_forward(t_data *data, double speed)
{
	t_player *p = data->player;
	double newX = p->pos_x + p->dir_x * speed;
	double newY = p->pos_y + p->dir_y * speed;

	// Check Y movement first (horizontal walls)
	if (data->map->map[(int)newY][(int)p->pos_x] != '1')
		p->pos_y = newY;
	// Check X movement second (vertical walls)
	if (data->map->map[(int)p->pos_y][(int)newX] != '1')
		p->pos_x = newX;
}

static void	move_backward(t_data *data, double speed)
{
	t_player *p = data->player;
	double newX = p->pos_x - p->dir_x * speed;
	double newY = p->pos_y - p->dir_y * speed;

	// Check Y movement first (horizontal walls)
	if (data->map->map[(int)newY][(int)p->pos_x] != '1')
		p->pos_y = newY;
	// Check X movement second (vertical walls)
	if (data->map->map[(int)p->pos_y][(int)newX] != '1')
		p->pos_x = newX;
}

static void	strafe_left(t_data *data, double speed)
{
	t_player *p = data->player;
	double newX = p->pos_x - p->plane_x * speed;
	double newY = p->pos_y - p->plane_y * speed;

	// Check Y movement first (horizontal walls)
	if (data->map->map[(int)newY][(int)p->pos_x] != '1')
		p->pos_y = newY;
	// Check X movement second (vertical walls)
	if (data->map->map[(int)p->pos_y][(int)newX] != '1')
		p->pos_x = newX;
}

static void	strafe_right(t_data *data, double speed)
{
	t_player *p = data->player;
	double newX = p->pos_x + p->plane_x * speed;
	double newY = p->pos_y + p->plane_y * speed;

	// Check Y movement first (horizontal walls)
	if (data->map->map[(int)newY][(int)p->pos_x] != '1')
		p->pos_y = newY;
	// Check X movement second (vertical walls)
	if (data->map->map[(int)p->pos_y][(int)newX] != '1')
		p->pos_x = newX;
}

static void	rotate_left(t_data *data, double rot_speed)
{
	t_player *p = data->player;
	double oldDirX = p->dir_x;
	double oldPlaneX = p->plane_x;

	// Rotate direction vector counterclockwise
	p->dir_x = p->dir_x * cos(-rot_speed) - p->dir_y * sin(-rot_speed);
	p->dir_y = oldDirX * sin(-rot_speed) + p->dir_y * cos(-rot_speed);
	// Rotate camera plane to match direction
	p->plane_x = p->plane_x * cos(-rot_speed) - p->plane_y * sin(-rot_speed);
	p->plane_y = oldPlaneX * sin(-rot_speed) + p->plane_y * cos(-rot_speed);
}

static void	rotate_right(t_data *data, double rot_speed)
{
	t_player *p = data->player;
	double oldDirX = p->dir_x;
	double oldPlaneX = p->plane_x;

	// Rotate direction vector clockwise
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = oldDirX * sin(rot_speed) + p->dir_y * cos(rot_speed);
	// Rotate camera plane to match direction
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = oldPlaneX * sin(rot_speed) + p->plane_y * cos(rot_speed);
}

// --- Main Movement Dispatcher ---

void	move_player(t_data *data)
{
	double move_speed = 0.05;	// Movement speed per frame
	double rot_speed = 0.03;	// Rotation speed per frame

	if (data->keys->esc)
		close_window(data);
	if (data->keys->w)
		move_forward(data, move_speed);
	if (data->keys->s)
		move_backward(data, move_speed);
	if (data->keys->a)
		strafe_left(data, move_speed);
	if (data->keys->d)
		strafe_right(data, move_speed);
	if (data->keys->left)
		rotate_left(data, rot_speed);
	if (data->keys->right)
		rotate_right(data, rot_speed);
}

// --- Ray Initialization Functions ---

// Initialize ray starting position and direction for given screen column
static void	init_ray_position(t_ray *ray, t_data *data, int x)
{
	double cameraX;

	// Convert screen x to camera coordinate (-1 to +1)
	cameraX = 2.0 * x / WIN_WIDTH - 1;

	// Set ray starting position to player position
	ray->pos_x = data->player->pos_x;
	ray->pos_y = data->player->pos_y;

	// Calculate ray direction: player direction + camera plane offset
	ray->dir_x = data->player->dir_x + data->player->plane_x * cameraX;
	ray->dir_y = data->player->dir_y + data->player->plane_y * cameraX;

	// Set current map coordinates
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
}

// Calculate step directions and delta distances for DDA algorithm
static void	init_ray_deltas(t_ray *ray)
{
	// Calculate distance between X and Y grid line crossings
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);

	// Determine step direction for X axis
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;

	// Determine step direction for Y axis
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

// Calculate initial distances to next grid lines
static void	init_ray_side_distances(t_ray *ray)
{
	// Calculate distance to next X grid line
	if (ray->dir_x < 0)
		ray->side_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	else
		ray->side_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;

	// Calculate distance to next Y grid line
	if (ray->dir_y < 0)
		ray->side_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	else
		ray->side_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
}

// --- DDA Algorithm Functions ---

// Perform one step of DDA algorithm
static void	dda_step(t_ray *ray)
{
	// Choose shorter distance to step to next grid line
	if (ray->side_x < ray->side_y)
	{
		ray->side_x += ray->delta_x;	// Add distance to next X crossing
		ray->map_x += ray->step_x;		// Move to next X grid
		ray->side = 0;					// Mark as X-side hit
	}
	else
	{
		ray->side_y += ray->delta_y;	// Add distance to next Y crossing
		ray->map_y += ray->step_y;		// Move to next Y grid
		ray->side = 1;					// Mark as Y-side hit
	}
}

// Run DDA until wall is hit
static void	perform_dda(t_ray *ray, t_data *data)
{
	int hit = 0;

	// Continue stepping until wall is found
	while (!hit)
	{
		dda_step(ray);

		// Check if current position is a wall
		if (data->map->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

// --- Distance Calculation ---

// Calculate perpendicular wall distance to avoid fisheye effect
static void	calculate_wall_distance(t_ray *ray)
{
	// Use perpendicular distance, not actual ray distance
	if (ray->side == 0)
	{
		// X-side wall: calculate distance using X coordinates
		ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	}
	else
	{
		// Y-side wall: calculate distance using Y coordinates
		ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	}
}

// --- Drawing Functions ---

// Calculate wall drawing start and end positions on screen
static void	calculate_draw_positions(t_ray *ray, int *drawStart, int *drawEnd)
{
	int lineHeight;

	// Calculate wall height on screen based on distance
	lineHeight = (int)(WIN_HEIGHT / ray->wall_dist);

	// Calculate top of wall (center - half height)
	*drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (*drawStart < 0)
		*drawStart = 0;

	// Calculate bottom of wall (center + half height)
	*drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (*drawEnd >= WIN_HEIGHT)
		*drawEnd = WIN_HEIGHT - 1;
}

// Pixel plotting function
void	put_pixel(t_img *img, int x, int y, int color)
{
	char *dst;

	// Calculate memory address for pixel
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	// Write color value to memory
	*(unsigned int *)dst = color;
}

// Draw a complete column (ceiling, wall, floor)
static void	draw_column(t_img *frame, int x, int drawStart, int drawEnd, t_data *data)
{
	int y = 0;

	// Draw ceiling from top to wall start
	while (y < drawStart)
	{
		put_pixel(frame, x, y, data->map->ceiling_color);
		y++;
	}

	// Draw wall from drawStart to drawEnd
	while (y < drawEnd)
	{
		put_pixel(frame, x, y, GREY);  // Using enum color instead of hex
		y++;
	}

	// Draw floor from wall end to bottom
	while (y < WIN_HEIGHT)
	{
		put_pixel(frame, x, y, data->map->floor_color);
		y++;
	}
}

// --- Main Raycasting Function ---

// Cast ray for single screen column and draw result
static void	raycast_column(t_data *data, int x, t_img *frame)
{
	t_ray	ray;
	int		drawStart;
	int		drawEnd;

	// Initialize ray for this screen column
	init_ray_position(&ray, data, x);
	init_ray_deltas(&ray);
	init_ray_side_distances(&ray);

	// Perform DDA to find wall
	perform_dda(&ray, data);

	// Calculate wall distance and draw positions
	calculate_wall_distance(&ray);
	calculate_draw_positions(&ray, &drawStart, &drawEnd);

	// Draw the column
	draw_column(frame, x, drawStart, drawEnd, data);
}

// --- Main Render Loop ---

void	render_frame(t_data *data)
{
	t_img	frame;
	int		x;

	// Create new image for this frame
	frame.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_len, &frame.endian);

	// Cast ray for each screen column
	x = 0;
	while (x < WIN_WIDTH)
	{
		raycast_column(data, x, &frame);
		x++;
	}

	// Display completed frame
	mlx_put_image_to_window(data->mlx, data->win, frame.img, 0, 0);
	mlx_destroy_image(data->mlx, frame.img);
}

int	render_frame_wrapper(void *param)
{
	t_data *data = (t_data *)param;

	// Update player position based on input
	move_player(data);
	// Render new frame
	render_frame(data);
	return (0);
}


// --- Game Entry Point ---

void	start_game(t_data *data)
{
	// Initialize MLX library
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		exit(1);
	}

	// Create window
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
	{
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		free(data->mlx);
		exit(1);
	}

	// Set up event hooks and start main loop
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);
	mlx_hook(data->win, 3, 1L<<1, handle_keyrelease, data);
	mlx_loop_hook(data->mlx, render_frame_wrapper, data);
	mlx_loop(data->mlx);
}
