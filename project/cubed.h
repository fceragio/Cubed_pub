/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:58 by federico          #+#    #+#             */
/*   Updated: 2025/07/02 19:45:00 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "../mlx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include <stdbool.h>

/*
for now NUM_RAYS has to be an odd number to alline perfectly with player->aim;
to avoid skipping colums, also WIN_WIDTH has to be a multiple of NUM_RAYS;
so for now NUM_RAYS 129, WIN_WIDTH 129 * 16;
*/

# define EPSILON 0.0001
# define BASE 43
# define WID_BASE (15 * 3)
# define RESOLUTION_1 (43)
# define RESOLUTION_2 (15)
# define RESOLUTION_3 (3)
# define WIN_WIDTH (WID_BASE * BASE)
# define WIN_HEIGHT ((WIN_WIDTH / 16) * 9)
# define TILE_SIZE 64

# define DEBUG_MODE 0
# define RESOLUTION RESOLUTION_2
# define WALL_SIZE (WIN_WIDTH / 2)
# define NUM_RAYS (WIN_WIDTH / RESOLUTION)
# define WID_RAYS (WIN_WIDTH / NUM_RAYS)
# define U_SEC 1000000
# define FPS 20
# define U_FPS (U_SEC / FPS)
# define SPEED 0.05
# define SENSITIVITY (M_PI / 64.0)
# define FOV (M_PI / 2.5)

# define MLX_DEFAULT 0
# define SUCCESS 0
# define FAILURE 1
# define MALLOC_ERR 4
# define MLX_ERR 5
# define BLACK 0x00000000
# define EMPTY 0x000000FF
# define FLOOR 0x656565FF
# define SEALING 0x00545454
# define WALL 0x00FFFFFF
# define PLAYER 0x00FF0000
# define AIM 0x00FFFF00
# define RAY 0x0000FF00
# define ERROR_COLOR 0xFF00FFFF
# define NORTH 9
# define SOUTH 8
# define EAST 7
# define WEST 6
# define SPACE 42

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*bit_addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_mlx_data;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ray
{
	double	x;
	double	y;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	step_x;
	double	step_y;
	double	hit_x;
	double	hit_y;
	double	len;
	double	distance;
	int		wall_side;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	t_ray	aim;
	t_ray	fov[NUM_RAYS];
}	t_player;

typedef struct s_sprite
{
	int			width;
	int			height;
	t_mlx_data	mlx_data;
}	t_sprite;

typedef struct s_map
{
	int			**arr;
	int			x_dimension;
	int			y_dimension;
	int			sealing_color;
	int			floor_color;
	t_sprite	*north_wall_texture;
	t_sprite	*south_wall_texture;
	t_sprite	*west_wall_texture;
	t_sprite	*east_wall_texture;
}	t_map;

typedef struct s_commands
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	l_arrow;
	bool	r_arrow;
}	t_commands;

typedef struct s_program
{
	t_mlx_data	mlx_data;
	t_map		*map;
	t_player	*player;
	t_commands	commands;
}	t_program;

double		safe_cos(double	angle);
double		safe_sin(double angle);
double		safe_tan(double angle);
void		safe_angle(double *angle);

void		program_init(t_program *program, t_map *map, t_player *player);
void		player_init(t_player *player, t_map map, t_program *program);
void		commands_init(t_program *program);
void		map_init(t_map *map, t_mlx_data *mlx);
t_sprite	*sprite_init(void *mlx, char *path);
void		vs_init(t_program *program);
int			program_close(t_program *program, int status);
void		destroy_map(t_map *map);
void		player_aim_init(t_player *player, t_program *program);
void		ray_init(t_ray *ray, t_player *player, double angle, t_program *program);

void		hook_handlers(t_program *program);
int			red_x_press_handling(t_program *program);
int			visibility_handling(t_program *program);
int			key_press_handling(int keysym, t_program *program);
int			key_release_handling(int keysym, t_program *program);
void		update_player(t_program *program);

void		put_pixel(t_program *program, int x, int y, int color);

void		rendering(t_program *program);
void		render(t_program *program);
int			loop_hook(t_program *program);
void		render_3d(t_program *program);
void		render_2d(t_program *program);

void		turn_pov(int keysym, t_program *program);
void		turn_left(t_program *program);
void		turn_right(t_program *program);

void		move_pov(int keysym, t_program *program);
void		move_forward(t_program *program);
void		move_backward(t_program *program);
void		move_left(t_program *program);
void		move_right(t_program *program);

int			not_wall(int x, int y, t_program *program);
int			find_wall_distance(double *distance, t_ray *ray, t_map *map, t_program *program);
double		find_vertical_hit_distance(t_ray *ray, t_map *map, t_point *hit, t_program *program);
double		find_horizontal_hit_distance(t_ray *ray, t_map *map, t_point *hit, t_program *program);

#endif