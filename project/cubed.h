/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:58 by federico          #+#    #+#             */
/*   Updated: 2025/07/10 14:32:48 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

//to make this faster, we could render sky and floor only where necessary.
//it would be a good idea also to check if the player actually moved or not,
//and render only if the movement button actually changed something in him

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

# define DEBUG_MODE 1

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TILE_SIZE 32

// win_width / 2 make them nice and squared
# define WALL_SIZE 960

//same as win_width or cleanly divides win_width
# define NUM_RAYS 1920

//win_width / num_rays
# define WID_RAYS 1

//1 / 20
# define SPEED 0.07

//m_pi / 64
# define SENSITIVITY 0.05

//m_pi / 2.5
# define FOV 1.5

# define EPSILON 0.0001
# define BUFFER_SIZE 64
# define MLX_DEFAULT 0
# define SUCCESS 0
# define FAILURE 1
# define OK 123
# define NOT_OK 0
# define MALLOC_ERR 4
# define MLX_ERR 5
# define WR_ERR 6

# define BLACK 0x00000000
# define EMPTY 0x000000FF
# define FLOOR 0x656565FF
# define SEALING 0x00545454
# define WALL 0x00FFFFFF
# define PLAYER 0x00FF0000
# define AIM 0x00FFFF00
# define RAY 0x0000FF00
# define ERROR_COLOR 0xFF00FFFF
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

# define M_SPACE ' '
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

typedef struct s_2d_ren_data
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;
	double	dx;
	double	dy;
	double	max_steps;
	double	step_x;
	double	step_y;
	double	x;
	double	y;
}	t_2d_ren_data;

typedef struct s_3d_ren_data
{
	int	y;
	int	y_start;
	int	y_end;
	int	color;
	int	i;
}	t_3d_ren_data;

typedef struct s_find_hit_data
{
	double	x;
	double	y;
	double	step_x;
	double	step_y;
	int		map_x;
	int		map_y;
}	t_find_hit_data;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

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

typedef struct s_map_blueprint
{
	bool	no_flag;
	bool	so_flag;
	bool	we_flag;
	bool	ea_flag;
	bool	c_flag;
	bool	f_flag;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*f;
	int		c_vals[COLOR_VALUES];
	int		f_vals[COLOR_VALUES];
	char	**split_c;
	char	**split_f;
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

//PARSING
t_map		*parsing(int argc, char *file_path, void *mlx);
t_map		*create_map(t_map_blueprint **blueprint, void *mlx);
void		create_map_blueprint(t_map_blueprint **blueprint, int fd);
int			blueprint_ok(t_map_blueprint *blueprint);
t_map		*blueprint_to_map(t_map_blueprint *blueprint, void *mlx);
//file checks
bool		check_file_name(char *file_path);
bool		check_file_access(char *file_path);
bool		cub_file_is_ok(int argc, char *file_path);
//fields checks
int			identify_line(char *line);
int			assign_line(char *line, t_map_blueprint *blueprint);
int			check_map_line(char *line);
int			assign_map_line(char *line, t_map_blueprint *blueprint);
int			check_n_line(char *line);
int			check_s_line(char *line);
int			check_w_line(char *line);
int			check_e_line(char *line);
int			check_c_line(char *line);
int			check_f_line(char *line);
int			assign_line_c(char *line, t_map_blueprint *blueprint);
int			assign_line_f(char *line, t_map_blueprint *blueprint);
int			assign_line_no(char *line, t_map_blueprint *blueprint);
int			assign_line_so(char *line, t_map_blueprint *blueprint);
int			assign_line_we(char *line, t_map_blueprint *blueprint);
int			assign_line_ea(char *line, t_map_blueprint *blueprint);
//blueprint
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
void		blueprint_prepare_fields(t_map_blueprint *blueprint);
int			trimmed_len(char *to_trim);
void		copy_only_second_string(char *to_copy, char *buffer);
char		*keep_only_second_string(char *to_trim);
int			find_next_number(char *str, int start);
int			measure_number(char *str, int start);
void		copy_number(char *to_copy, int *start, char *buffer);
char		**split_second_string_commas(char *to_split);
//map
t_map		*map_init(void);
int			sprite_init(t_sprite **result, void *mlx, char *path);
void		destroy_map(t_map *map);
void		destroy_texture(t_sprite *sprite);
int			blueprint_ok(t_map_blueprint *blueprint);
int			blueprint_f_c_colors(t_map_blueprint *blueprint);
int			string_to_int(char *str);
int			sprite_init(t_sprite **result, void *mlx, char *path);
int			set_map_textures(t_map *map, t_map_blueprint *blueprint, void *mlx);
void		copy_array(t_map *map, t_list *list);
void		set_map_array(t_map *map, t_map_blueprint *blueprint);
int			set_map_colors(t_map *map, t_map_blueprint *blueprint);
t_map		*blueprint_to_map(t_map_blueprint *blueprint, void *mlx);
//get_next_line
char		*get_next_line(int fd);
void		create_list_till_newl(t_list **list, int fd);
void		add_node(t_list **list, char *buffer);
int			new_line(t_list *list);
t_list		*find_last(t_list *list);
char		*concatenate_lines(t_list *list);
void		cleanup(t_list **list);
void		freeall_save_leftover(t_list **list,
				t_list *new_list, char *leftover);
size_t		chars_to_newl(t_list *list);
void		cat_nodes(t_list *list, char *next_line);
void		clear_nextlines(int fd);
//utils
int			str_len(char *str);
void		print_str(char *str);
void		print_error(char *str);
void		manage_critical_error(char *msg, int stat);
t_list		*list_last(t_list *list);
void		list_append(char *content, t_list **list);
int			list_len(t_list *list);
int			content_max_len(t_list *list);

//RENDERING 3D
void		put_pixel(t_program *program, int x, int y, int color);
void		render_3d(t_program *program);
void		render_sealing(t_program *program);
void		render_floor(t_program *program);
void		render_walls(t_program *program);
void		put_ray_pixels(t_point pixel, t_program *program);
int			get_wall_color(t_map *map, t_ray ray,
				t_point pixel, int y_len);
int			get_texture_color(int x, int y, t_sprite texture);
int			get_north_wall_color(t_map *map, t_ray ray,
				t_point pixel, int y_len);
int			get_south_wall_color(t_map *map, t_ray ray,
				t_point pixel, int y_len);
int			get_west_wall_color(t_map *map, t_ray ray,
				t_point pixel, int y_len);
int			get_east_wall_color(t_map *map, t_ray ray,
				t_point pixel, int y_len);
//math
double		safe_cos(double angle);
double		safe_sin(double angle);
double		safe_tan(double angle);
void		safe_angle(double *angle);
//inits
void		program_init(void *mlx, t_program *program,
				t_map *map, t_player *player);
void		player_init(t_player *player, t_map map, t_program *program);
void		vs_init(void *mlx, t_program *program);
int			program_close(t_program *program, int status);
void		player_aim_init(t_player *player, t_program *program);
void		ray_init(t_ray *ray, t_player *player,
				double angle, t_program *program);
int			not_wall(int x, int y, t_program *program);
int			find_wall_distance(double *distance,
				t_ray *ray, t_map *map, t_program *program);
double		find_vertical_hit_distance(t_ray *ray,
				t_map *map, t_point *hit, t_program *program);
double		find_horizontal_hit_distance(t_ray *ray,
				t_map *map, t_point *hit, t_program *program);
//events
void		hook_handlers(t_program *program);
int			red_x_press_handling(t_program *program);
int			visibility_handling(t_program *program);
int			key_press_handling(int keysym, t_program *program);
void		rendering(t_program *program);
void		render(t_program *program);
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

//DEBUG
void		render_2d(t_program *program);
void		render_2d_map(t_map *map, t_program *program);
void		render_2d_player(t_player *player, t_program *program);
void		render_2d_rays(t_player *player, t_program *program);
void		render_2d_ray(t_ray ray, t_program *program, int color);
void		put_empty_2d(int i, int j, t_program *program);
void		put_wall_2d(int i, int j, t_program *program);
void		reset_2d(t_program *program);

#endif