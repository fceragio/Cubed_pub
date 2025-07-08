/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:20:41 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 01:21:13 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	not_wall(int x, int y, t_program *program)
{
	int	**arr;
	int	x_limit;
	int	y_limit;

	x_limit = program->map->x_dimension;
	y_limit = program->map->y_dimension;
	if (x < 0 || x >= x_limit || y < 0 || y >= y_limit)
		return (0);
	arr = program->map->arr;
	if (arr[y][x] == 1)
		return (0);
	return (1);
}

int	find_wall_distance(double *distance,
		t_ray *ray, t_map *map, t_program *program)
{
	double	vrt_dist;
	double	hrz_dist;
	t_point	vrt_hit;
	t_point	hrz_hit;

	vrt_dist = find_vertical_hit_distance(ray, map, &vrt_hit, program);
	hrz_dist = find_horizontal_hit_distance(ray, map, &hrz_hit, program);
	if (vrt_dist < hrz_dist)
	{
		*distance = vrt_dist;
		ray->hit_x = vrt_hit.x;
		ray->hit_y = vrt_hit.y;
		if (ray->angle > (M_PI / 2) && ray->angle < (3 * M_PI / 2))
			return (EAST);
		return (WEST);
	}
	*distance = hrz_dist;
	ray->hit_x = hrz_hit.x;
	ray->hit_y = hrz_hit.y;
	if (ray->angle < M_PI)
		return (NORTH);
	return (SOUTH);
}
