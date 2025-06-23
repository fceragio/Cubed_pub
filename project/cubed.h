/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:58 by federico          #+#    #+#             */
/*   Updated: 2025/06/23 23:10:50 by federico         ###   ########.fr       */
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

# define DEBUG_MODE 1
# define WIN_WIDTH	960
# define WIN_HEIGHT 540
# define TILE_SIZE 64
# define SPEED 0.05
# define MLX_DEFAULT 0
# define SUCCESS 0
# define FAILURE 1
# define MALLOC_ERR 4
# define MLX_ERR 5
# define BLACK 0x00000000
# define EMPTY 0x000000FF
# define WALL 0x00FFFFFF
# define PLAYER 0x00FF0000
# define NORTH 9
# define SOUTH 8
# define EAST 7
# define WEST 6

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_map
{
	int		**arr;
	int		dimension;
}	t_map;

typedef struct s_program
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*bit_addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_map		*map;
	t_player	*player;
}	t_program;

void		player_init(t_player *player, t_map map);
void		map_init(t_map *map);
void		program_init(t_program *program);
int			program_close(t_program *program, int status);
void		destroy_map(t_map *map);

void		hook_handlers(t_program *program);
int			red_x_press_handling(t_program *program);
int			visibility_handling(t_program *program);
int			key_press_handling(int keysym, t_program *program);

void		put_pixel(t_program *program, int x, int y, int color);

void		render(t_program *program);
void		render_2d(t_program *program);

double		lerp(double a, double b, double t);

void		turn_pov(int keysym, t_program *program);
void		turn_left(t_program *program);
void		turn_right(t_program *program);

void		move_pov(int keysym, t_program *program);
void		move_forward(t_program *program);
void		move_backward(t_program *program);
void		move_left(t_program *program);
void		move_right(t_program *program);

int			not_wall(int x, int y, t_program *program);

#endif