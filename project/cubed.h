/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:58 by federico          #+#    #+#             */
/*   Updated: 2025/06/22 02:48:10 by federico         ###   ########.fr       */
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

# define WIN_WIDTH	960
# define WIN_HEIGHT 540
# define TILE_SIZE 32
# define MLX_DEFAULT 0
# define SUCCESS 0
# define FAILURE 1
# define MALLOC_ERR 4
# define MLX_ERR 5
# define EMPTY 0x00000000
# define WALL 0x00FFFFFF
# define PLAYER 0x00FFFF00
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
	int		width;
	int		height;
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
int			key_press_handling(int keysym, t_program *program);

void		put_pixel(t_program *program, int x, int y, int color);
// double	scale(double unscaled, double old_max, double new_min, double new_max);

void		render_2d(t_program *program);

#endif