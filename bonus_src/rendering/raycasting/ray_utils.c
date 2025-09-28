/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:39:40 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/28 18:11:55 by federico         ###   ########.fr       */
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

void	detect_wall_side(t_hit_data *data, t_ray *ray)
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

static bool	x_axis_done(t_hit_data *data, t_ray *ray, t_program *program)
{
	data->hit_axis = X_AXIS;
	data->distance = data->x_side_d;
	data->map_x += ray->step_x;
	if (is_hit_door(data->map_x, data->map_y, program))
	{
		ray->door = true;
		return (SUCCESS);
	}
	if (is_hit_wall(data->map_x, data->map_y, program))
		return (SUCCESS);
	return (FAILURE);
}

static bool	y_axis_done(t_hit_data *data, t_ray *ray, t_program *program)
{
	data->hit_axis = Y_AXIS;
	data->distance = data->y_side_d;
	data->map_y += ray->step_y;
	if (is_hit_door(data->map_x, data->map_y, program))
	{
		ray->door = true;
		return (SUCCESS);
	}
	if (is_hit_wall(data->map_x, data->map_y, program))
		return (SUCCESS);
	return (FAILURE);
}

double	find_distance_to_wall(t_ray *ray, t_program *program)
{
	t_hit_data	data;

	setup_hit_data(&data, ray);
	while (!is_out_of_bounds(data.map_x, data.map_y, program))
	{
		if (data.x_side_d < data.y_side_d)
		{
			if (x_axis_done(&data, ray, program) == SUCCESS)
				return (detect_wall_side(&data, ray), data.distance);
			data.x_side_d += data.x_delta_d;
		}
		else
		{
			if (y_axis_done(&data, ray, program) == SUCCESS)
				return (detect_wall_side(&data, ray), data.distance);
			data.y_side_d += data.y_delta_d;
		}
	}
	return (detect_wall_side(&data, ray), data.distance);
}
