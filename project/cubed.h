/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:58 by federico          #+#    #+#             */
/*   Updated: 2025/07/07 18:38:18 by federico         ###   ########.fr       */
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
# include <fcntl.h>

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
# define BUFFER_SIZE 64

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

# define M_SPACE 42
# define M_NO 101
# define M_SO 102
# define M_WE 103
# define M_EA 104
# define M_C 105
# define M_F 106
# define M_MAP 107
# define M_SKIP 108
# define M_ERR 109
# define COLOR_VALUES 3

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

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_map_blueprint
{
	bool	No_flag;
	bool	So_flag;
	bool	We_flag;
	bool	Ea_flag;
	bool	C_flag;
	bool	F_flag;
	char	*No;
	char	*So;
	char	*We;
	char	*Ea;
	char	*C;
	char	*F;
	char	**split_C;
	char	**split_F;
	t_list	*map_list;
	char	**char_map;
	int		x_len;
	int		y_len;
}	t_map_blueprint;

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

char	*get_next_line(int fd);
void	create_list_till_newl(t_list **list, int fd);
void	add_node(t_list **list, char *buffer);
int		new_line(t_list *list);
t_list	*find_last(t_list *list);
char	*concatenate_lines(t_list	*list);
void	cleanup(t_list **list);
void	freeall_save_leftover(t_list **list, t_list *new_list, char	*leftover);
size_t	chars_to_newl(t_list *list);
void	cat_nodes(t_list *list, char *next_line);


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

int			str_len(char *str);
void		print_str(char *str);
void		print_error(char *str);




t_map		*parsing(int argc, char *file_path);
t_map		*create_map(t_map_blueprint **blueprint);
void		create_map_blueprint(t_map_blueprint **blueprint, int fd);
int			blueprint_ok(t_map_blueprint *blueprint);
t_map		*blueprint_to_map(t_map_blueprint *blueprint);

t_list		*list_last(t_list *list);
void		list_append(char *content, t_list **list);
int			list_len(t_list *list);
int			content_max_len(t_list *list);

int			identify_line(char *line);
int			assign_line(char *line, t_map_blueprint *blueprint);
int			check_map_line(char *line);
int			assign_map_line(char *line, t_map_blueprint *blueprint);
char		*get_next_line(int fd);

void		add_node(t_list **list, char *buffer);
int			new_line(t_list *list);
t_list		*find_last(t_list *list);
void		cleanup(t_list **list);
void		freeall_save_leftover(t_list **list, t_list *new_list, char	*leftover);
void		create_list_till_newl(t_list **list, int fd);
char		*concatenate_lines(t_list	*list);
void		cat_nodes(t_list *list, char *next_line);
size_t		chars_to_newl(t_list *list);

int			check_N_line(char *line);
int			check_S_line(char *line);
int			check_W_line(char *line);
int			check_E_line(char *line);
int			check_C_line(char *line);
int			check_F_line(char *line);

bool		check_file_name(char *file_path);
bool		check_file_access(char *file_path);
bool		cub_file_is_ok(int argc, char *file_path);

void		blueprint_init(t_map_blueprint *blueprint);
void		clear_char_matrix(char **char_map);
void		clear_blueprint(t_map_blueprint **blueprint);

void		create_char_map(t_map_blueprint *blueprint);
void		zero_char_map(t_map_blueprint *blueprint);
void		malloc_char_map(t_map_blueprint *blueprint);
void		set_char_map(t_map_blueprint *blueprint);

int			spawns_ok(t_map_blueprint *blueprint);
int			flood_fill(t_map_blueprint *blueprint, char **map, int x, int y);
int			map_is_closed(t_map_blueprint *blueprint);
int			blueprint_map_ok(t_map_blueprint *blueprint);

int			assign_line_C(char *line, t_map_blueprint *blueprint);
int			assign_line_F(char *line, t_map_blueprint *blueprint);
int			assign_line_NO(char *line, t_map_blueprint *blueprint);
int			assign_line_SO(char *line, t_map_blueprint *blueprint);
int			assign_line_WE(char *line, t_map_blueprint *blueprint);
int			assign_line_EA(char *line, t_map_blueprint *blueprint);


void		blueprint_prepare_fields(t_map_blueprint *blueprint);

#endif