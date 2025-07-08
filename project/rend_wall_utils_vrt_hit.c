/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_wall_utils_vrt_hit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:21:28 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 01:21:51 by federico         ###   ########.fr       */
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
	double	x;
	double	y;
	double	step_x;
	double	step_y;
	int		map_x;
	int		map_y;

	set_vertical_base(&x, &y, ray);
	step_x = ray->step_x * 1.0;
	step_y = step_x * (ray->dir_y / ray->dir_x);
	while (x >= 0 && x < map->x_dimension && y >= 0 && y < map->y_dimension)
	{
		set_vertical_map(&map_x, x, ray);
		map_y = (int)y;
		if (!not_wall(map_x, map_y, program))
		{
			hit->x = x;
			hit->y = y;
			return hypot(x - ray->x, y - ray->y);
		}
		x += step_x;
		y += step_y;
	}
	hit->x = x;
	hit->y = y;
	return (INFINITY);
}
