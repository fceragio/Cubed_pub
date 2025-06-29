/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:22:10 by federico          #+#    #+#             */
/*   Updated: 2025/06/29 01:52:06 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	render_sealing(t_program *program)
{
	int	x;
	int	y;

	x = 0;
	while (x <= WIN_WIDTH)
	{
		y = 0;
		while (y < (WIN_HEIGHT / 2))
		{
			put_pixel(program, x, y, program->map->sealing_color);
			y++;
		}
		x++;
	}
}

static void	render_floor(t_program *program)
{
	int	x;
	int	y;

	x = 0;
	while (x <= WIN_WIDTH)
	{
		y = (WIN_HEIGHT / 2);
		while (y < WIN_HEIGHT)
		{
			put_pixel(program, x, y, program->map->floor_color);
			y++;
		}
		x++;
	}
}

static void	put_ray_pixels(int x, int i, t_program *program)
{
	int	y;
	int	y_end;

	y = (WIN_HEIGHT / 2) - (SPRITE_SIZE / program->player->fov[i].len);
	y_end = (WIN_HEIGHT / 2) + (SPRITE_SIZE / program->player->fov[i].len);
	while (y <= y_end)
	{
		put_pixel(program, x, y, WALL);
		y++;
	}
}

static void	render_walls(t_program *program)
{
	int	i;
	int	x;

	i = 0;
	while (i <= NUM_RAYS)
	{
		x = WID_RAYS * i;
		while (x <= (WID_RAYS * (i + 1)))
		{
			put_ray_pixels(x, i, program);
			x++;
		}
		i++;
	}
}

void	render_3d(t_program *program)
{
	render_sealing(program);
	render_floor(program);
	render_walls(program);
}
