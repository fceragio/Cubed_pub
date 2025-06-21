/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:23:59 by federico          #+#    #+#             */
/*   Updated: 2025/06/22 02:29:06 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	put_empty(int i, int j, t_program *program)
{
	int	x;
	int	y;
	int	x_end;
	int	y_end;

	x_end = i * TILE_SIZE + TILE_SIZE;
	y_end = j * TILE_SIZE + TILE_SIZE;
	x = i * TILE_SIZE;
	while (x < x_end)
	{
		y = j * TILE_SIZE;
		while(y < y_end)
		{
			put_pixel(program, x, y, EMPTY);
			y++;
		}
		x++;
	}
}

static void	put_wall(int i, int j, t_program *program)
{
	int	x;
	int	y;
	int	x_end;
	int	y_end;

	x_end = i * TILE_SIZE + TILE_SIZE;
	y_end = j * TILE_SIZE + TILE_SIZE;
	x = i * TILE_SIZE;
	while (x < x_end)
	{
		y = j * TILE_SIZE;
		while(y < y_end)
		{
			put_pixel(program, x, y, WALL);
			y++;
		}
		x++;
	}
}

static void	render_2d_map(t_map *map, t_program *program)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->arr[i][j] == 1)
				put_wall(i, j, program);
			else
				put_empty(i, j, program);
			j++;
		}
		i++;
	}
}
static void render_2d_player(t_player *player, t_program *program)
{
	put_pixel(program, player->x, player->y, PLAYER);
}

void	render_2d(t_program *program)
{
	render_2d_map(program->map, program);
	render_2d_player(program->player, program);
	mlx_put_image_to_window(program->mlx, program->win, program->img, MLX_DEFAULT, MLX_DEFAULT);
}
