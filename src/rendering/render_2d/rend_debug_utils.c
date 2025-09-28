/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_debug_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:58:50 by federico          #+#    #+#             */
/*   Updated: 2025/09/09 21:10:46 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_2d_ray(t_ray ray, t_program *program, int color)
{
	t_2d_ren_data	data;
	int				i;

	data.x0 = ray.x * TILE_SIZE;
	data.y0 = ray.y * TILE_SIZE;
	data.x1 = ray.hit_x * TILE_SIZE;
	data.y1 = ray.hit_y * TILE_SIZE;
	data.dx = data.x1 - data.x0;
	data.dy = data.y1 - data.y0;
	data.max_steps = fmax(fabs(data.dx), fabs(data.dy));
	data.step_x = data.dx / data.max_steps;
	data.step_y = data.dy / data.max_steps;
	data.x = data.x0;
	data.y = data.y0;
	i = 0;
	while (i <= (int)data.max_steps)
	{
		put_pixel(program, (int)data.x, (int)data.y, color);
		data.x += data.step_x;
		data.y += data.step_y;
		i++;
	}
}

void	put_empty_2d(int i, int j, t_program *program)
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
		while (y < y_end - 1)
		{
			put_pixel(program, x, y, EMPTY);
			y++;
		}
		x++;
	}
}

void	put_wall_2d(int i, int j, t_program *program)
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
		while (y < y_end - 1)
		{
			put_pixel(program, x, y, WALL);
			y++;
		}
		x++;
	}
}

void	reset_2d(t_program *program)
{
	int	x;
	int	y;

	x = 0;
	while (x < (program->map->x_dimension * TILE_SIZE))
	{
		y = 0;
		while (y < (program->map->y_dimension * TILE_SIZE))
		{
			put_pixel(program, x, y, BLACK);
			y++;
		}
		x++;
	}
}
