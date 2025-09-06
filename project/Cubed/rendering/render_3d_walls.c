/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:22:52 by federico          #+#    #+#             */
/*   Updated: 2025/09/03 22:59:15 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	put_ray_pixels_data_init(t_3d_ren_data *data,
		t_point pixel, t_program *program)
{
	data->i = pixel.y;
	data->y_start = (WIN_HEIGHT / 2) - (
			WALL_SIZE / program->player->fov[data->i].distance) / 2;
	data->y_end = (WIN_HEIGHT / 2) + (
			WALL_SIZE / program->player->fov[data->i].distance) / 2;
	data->y = 0;
}

void	put_ray_pixels(t_point pixel, t_program *program)
{
	t_3d_ren_data	data;

	put_ray_pixels_data_init(&data, pixel, program);
	while (data.y <= data.y_start)
	{
		put_pixel(program, pixel.x, data.y, program->map->sealing_color);
		data.y++;
	}
	while (data.y < data.y_end && data.y < WIN_HEIGHT)
	{
		pixel.y = data.y;
		data.color = get_wall_color(program->map,
				program->player->fov[data.i], pixel, data.y_end - data.y_start);
		put_pixel(program, pixel.x, pixel.y, data.color);
		data.y++;
	}
	while (data.y < WIN_HEIGHT)
	{
		put_pixel(program, pixel.x, data.y, program->map->floor_color);
		data.y++;
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
