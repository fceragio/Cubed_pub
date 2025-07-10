/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:22:10 by federico          #+#    #+#             */
/*   Updated: 2025/07/10 14:32:02 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	render_3d(t_program *program)
{
	render_walls(program);
}

void	render_sealing(t_program *program)
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

void	render_floor(t_program *program)
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

void	render_walls(t_program *program)
{
	t_point	pixel;
	int		i;
	int		x;

	i = 0;
	while (i <= NUM_RAYS)
	{
		x = WID_RAYS * i;
		while (x <= (WID_RAYS * (i + 1)))
		{
			pixel.x = x;
			pixel.y = i;
			put_ray_pixels(pixel, program);
			x++;
		}
		i++;
	}
}
