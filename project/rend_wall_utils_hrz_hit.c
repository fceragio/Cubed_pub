/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_wall_utils_hrz_hit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:22:06 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 01:52:52 by federico         ###   ########.fr       */
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
	double	x;
	double	y;
	double	step_x;
	double	step_y;
	int		map_x;
	int		map_y;

	set_horizontal_base(&x, &y, ray);
	step_y = ray->step_y * 1.0;
	step_x = step_y * (ray->dir_x / ray->dir_y);
	while (x >= 0 && x < map->x_dimension && y >= 0 && y < map->y_dimension)
	{
		set_horizontal_map(&map_y, y, ray);
		map_x = (int)(x);
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
