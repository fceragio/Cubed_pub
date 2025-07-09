/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_wall_utils_vrt_hit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:21:28 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 16:56:31 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_vertical_base(double *x, double *y, t_ray *ray)
{
	double	dx;
	double	dy;

	if (ray->step_x > 0)
		*x = floor(ray->x) + 1.0;
	else
		*x = floor(ray->x);
	dx = *x - ray->x;
	dy = dx * (ray->dir_y / ray->dir_x);
	*y = ray->y + dy;
}

static void	set_vertical_map(int *map_x, double x, t_ray *ray)
{
	if (ray->step_x < 0)
		*map_x = (int)(x - 1);
	else
		*map_x = (int)(x);
}

double	find_vertical_hit_distance(t_ray *ray,
			t_map *map, t_point *hit, t_program *program)
{
	t_find_hit_data	data;

	set_vertical_base(&data.x, &data.y, ray);
	data.step_x = ray->step_x * 1.0;
	data.step_y = data.step_x * (ray->dir_y / ray->dir_x);
	while (data.x >= 0 && data.x < map->x_dimension
		&& data.y >= 0 && data.y < map->y_dimension)
	{
		set_vertical_map(&data.map_x, data.x, ray);
		data.map_y = (int)data.y;
		if (!not_wall(data.map_x, data.map_y, program))
		{
			hit->x = data.x;
			hit->y = data.y;
			return (hypot(data.x - ray->x, data.y - ray->y));
		}
		data.x += data.step_x;
		data.y += data.step_y;
	}
	hit->x = data.x;
	hit->y = data.y;
	return (INFINITY);
}
