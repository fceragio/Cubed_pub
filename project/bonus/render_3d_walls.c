/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:22:52 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 16:41:16 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	put_ray_pixels(t_point pixel, t_program *program)
{
	int	y;
	int	y_start;
	int	y_end;
	int	color;
	int	i;

	i = pixel.y;
	y_start = (WIN_HEIGHT / 2) - (
			WALL_SIZE / program->player->fov[i].distance) / 2;
	y_end = (WIN_HEIGHT / 2) + (
			WALL_SIZE / program->player->fov[i].distance) / 2;
	y = y_start;
	while (y <= y_end)
	{
		pixel.y = y;
		color = get_wall_color(program->map,
				program->player->fov[i], pixel, y_end - y_start);
		put_pixel(program, pixel.x, pixel.y, color);
		y++;
	}
}

int	get_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	if (ray.wall_side == NORTH)
		return (get_north_wall_color(map, ray, pixel, y_len));
	else if (ray.wall_side == SOUTH)
		return (get_south_wall_color(map, ray, pixel, y_len));
	else if (ray.wall_side == WEST)
		return (get_west_wall_color(map, ray, pixel, y_len));
	else if (ray.wall_side == EAST)
		return (get_east_wall_color(map, ray, pixel, y_len));
	return (FAILURE);
}
