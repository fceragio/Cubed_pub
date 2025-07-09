/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_wall_utils_hrz_hit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:22:06 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 16:56:25 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_horizontal_base(double *x, double *y, t_ray *ray)
{
	double	dx;
	double	dy;

	if (ray->step_y > 0)
		*y = floor(ray->y) + 1.0;
	else
		*y = floor(ray->y);
	dy = *y - ray->y;
	dx = dy * (ray->dir_x / ray->dir_y);
	*x = ray->x + dx;
}

static void	set_horizontal_map(int *map_y, double y, t_ray *ray)
{
	if (ray->step_y < 0)
		*map_y = (int)(y - 1);
	else
		*map_y = (int)(y);
}

double	find_horizontal_hit_distance(t_ray *ray,
		t_map *map, t_point *hit, t_program *program)
{
	t_find_hit_data	data;

	set_horizontal_base(&data.x, &data.y, ray);
	data.step_y = ray->step_y * 1.0;
	data.step_x = data.step_y * (ray->dir_x / ray->dir_y);
	while (data.x >= 0 && data.x < map->x_dimension
		&& data.y >= 0 && data.y < map->y_dimension)
	{
		set_horizontal_map(&data.map_y, data.y, ray);
		data.map_x = (int)(data.x);
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
