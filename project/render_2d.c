/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:23:59 by federico          #+#    #+#             */
/*   Updated: 2025/06/24 00:18:09 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	put_empty_2d(int i, int j, t_program *program)
{
	int	x;
	int	y;
	int	x_end;
	int	y_end;

	x_end = i * TILE_SIZE + TILE_SIZE;
	y_end = j * TILE_SIZE + TILE_SIZE;
	x = i * TILE_SIZE + 1;
	while (x < x_end - 1)
	{
		y = j * TILE_SIZE + 1;
		while(y < y_end - 1)
		{
			put_pixel(program, x, y, EMPTY);
			y++;
		}
		x++;
	}
}

static void	put_wall_2d(int i, int j, t_program *program)
{
	int	x;
	int	y;
	int	x_end;
	int	y_end;

	x_end = i * TILE_SIZE + TILE_SIZE;
	y_end = j * TILE_SIZE + TILE_SIZE;
	x = i * TILE_SIZE + 1;
	while (x < x_end - 1)
	{
		y = j * TILE_SIZE + 1;
		while(y < y_end - 1)
		{
			put_pixel(program, x, y, WALL);
			y++;
		}
		x++;
	}
}

static void	reset_2d(t_program *program)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			put_pixel(program, x, y, BLACK);
			y++;
		}
		x++;
	}
}

static void	render_2d_map(t_map *map, t_program *program)
{
	int	x;
	int	y;

	reset_2d(program);
	x = 0;
	while (x < map->dimension)
	{
		y = 0;
		while (y < map->dimension)
		{
			if (map->arr[y][x] == 1)
				put_wall_2d(x, y, program);
			else
				put_empty_2d(x, y, program);
			y++;
		}
		x++;
	}
}
static void render_2d_player(t_player *player, t_program *program)
{
	int	i;
	int	j;

	i = -1;
	while (i < 2)
	{
		j = -1;
		while (j < 2)
		{
			put_pixel(program, player->x * TILE_SIZE + i, player->y * TILE_SIZE + j, PLAYER);
			j++;
		}
		i++;
	}
}

static void	render_2d_rays(t_player *player, t_program *program)
{
	
}

void	render_2d(t_program *program)
{
	render_2d_map(program->map, program);
	render_2d_player(program->player, program);
	render_2d_rays(program->player, program);
	mlx_put_image_to_window(program->mlx, program->win, program->img, MLX_DEFAULT, MLX_DEFAULT);
}
