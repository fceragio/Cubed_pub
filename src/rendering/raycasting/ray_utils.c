/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:39:40 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/21 17:35:52 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_hit_data(t_hit_data *data, t_ray *ray)
{
	data->map_x = (int)ray->x;
	data->map_y = (int)ray->y;
	if (ray->dir_x < 0)
		data->x_side_d = (ray->x - data->map_x) / fabs(ray->dir_x);
	else
		data->x_side_d = (data->map_x + 1.0 - ray->x) / fabs(ray->dir_x);
	if (ray->dir_y < 0)
		data->y_side_d = (ray->y - data->map_y) / fabs(ray->dir_y);
	else
		data->y_side_d = (data->map_y + 1.0 - ray->y) / fabs(ray->dir_y);
	if (ray->dir_x == 0)
		data->x_delta_d = INFINITY;
	else
		data->x_delta_d = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		data->y_delta_d = INFINITY;
	else
		data->y_delta_d = fabs(1.0 / ray->dir_y);
}

bool	is_out_of_bounds(int x, int y, t_program *program)
{
	int	x_max_idx;
	int	y_max_idx;

	x_max_idx = program->map->x_dimension - 1;
	y_max_idx = program->map->y_dimension - 1;
	if (x < 0 || x > x_max_idx
		|| y < 0 || y > y_max_idx)
		return (true);
	return (false);
}

bool	is_hit_wall(int x, int y, t_program *program)
{
	int	**map_2d_arr;

	map_2d_arr = program->map->arr;
	if (map_2d_arr[y][x] == 1)
		return (true);
	return (false);
}

static void	detect_wall_side(t_hit_data *data, t_ray *ray)
{
	if (data->hit_axis == X_AXIS)
	{
		if (ray->step_x > 0)
			ray->wall_side = WEST;
		else
			(ray->wall_side = EAST);
	}
	else if (ray->step_y > 0)
		ray->wall_side = NORTH;
	else
		ray->wall_side = SOUTH;
	return ;
}

double	find_distance_to_wall(t_ray *ray, t_program *program)
{
	t_hit_data	data;

	setup_hit_data(&data, ray);
	while (!is_out_of_bounds(data.map_x, data.map_y, program))
	{
		if (data.x_side_d < data.y_side_d)
		{
			data.hit_axis = X_AXIS;
			data.distance = data.x_side_d;
			data.map_x += ray->step_x;
			if (is_hit_wall(data.map_x, data.map_y, program))
				return (detect_wall_side(&data, ray), data.distance);
			data.x_side_d += data.x_delta_d;
		}
		else
		{
			data.hit_axis = Y_AXIS;
			data.distance = data.y_side_d;
			data.map_y += ray->step_y;
			if (is_hit_wall(data.map_x, data.map_y, program))
				return (detect_wall_side(&data, ray), data.distance);
			data.y_side_d += data.y_delta_d;
		}
	}
	return (detect_wall_side(&data, ray), data.distance);
}
