/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:22:10 by federico          #+#    #+#             */
/*   Updated: 2025/07/01 17:34:25 by federico         ###   ########.fr       */
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

int	get_north_wall_color(t_map *map, int i, int len)
{
	return (0x00000000);
}
int	get_south_wall_color(t_map *map, int i, int len)
{
	return (0x00FFFFFFFF);
}
int	get_west_wall_color(t_map *map, int i, int len)
{
	return (0x00696969);
}
int	get_east_wall_color(t_map *map, int i, int len)
{
	return (0x00969696);
}

static int	get_wall_color(t_map *map, int wall_side, int i, int len)
{
	if (wall_side == NORTH)
		return (get_north_wall_color(map, i, len));
	else if (wall_side == SOUTH)
		return (get_south_wall_color(map, i, len));
	else if (wall_side == WEST)
		return (get_west_wall_color(map, i, len));
	else if (wall_side == EAST)
		return (get_east_wall_color(map, i, len));
	return (FAILURE);
}

static void	put_ray_pixels(int x, int i, t_program *program)
{
	int	y;
	int	y_start;
	int	y_end;
	int	color;

	y_start = (WIN_HEIGHT / 2) - (WALL_SIZE / program->player->fov[i].distance);
	y_end = (WIN_HEIGHT / 2) + (WALL_SIZE / program->player->fov[i].distance);
	y = y_start;
	while (y <= y_end)
	{
		color = get_wall_color(program->map, program->player->fov[i].wall_side, y, y_end - y_start);
		put_pixel(program, x, y, color);
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
