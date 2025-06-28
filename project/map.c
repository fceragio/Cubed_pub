/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:21:34 by federico          #+#    #+#             */
/*   Updated: 2025/06/29 01:50:08 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	not_wall(int x, int y, t_program *program)
{
	int	**arr;
	int	limit;

	limit = program->map->dimension;
	if (x < 0 || x >= limit || y < 0 || y >= limit)
		return (0);
	arr = program->map->arr;
	if (arr[y][x] == 1)
		return (0);
	return (1);
}

int	find_wall_distance(double *distance, t_ray *ray, t_map *map, t_program *program)
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

double	find_vertical_hit_distance(t_ray *ray, t_map *map, t_point *hit, t_program *program)
{
	double x, y;
	double dx, dy;
	double delta_x, delta_y;

	// Calcola la prima intersezione verticale
	if (ray->step_x > 0)
		x = floor(ray->x) + 1.0;
	else
		x = floor(ray->x);

	dx = x - ray->x;
	dy = dx * (ray->dir_y / ray->dir_x);
	y = ray->y + dy;

	// Calcola incremento per ciascun passo
	delta_x = ray->step_x * 1.0;
	delta_y = delta_x * (ray->dir_y / ray->dir_x);

	// Itera finché non colpisce un muro
	while (x >= 0 && x < map->dimension && y >= 0 && y < map->dimension)
	{
		int map_x = (int)(x + (ray->step_x < 0 ? -1 : 0)); // lato corretto
		int map_y = (int)(y);

		if (!not_wall(map_x, map_y, program))
		{
			hit->x = x;
			hit->y = y;
			return hypot(x - ray->x, y - ray->y);
		}
		x += delta_x;
		y += delta_y;
	}
	hit->x = x;
	hit->y = y;
	return INFINITY;
}

double	find_horizontal_hit_distance(t_ray *ray, t_map *map, t_point *hit, t_program *program)
{
	double x, y;
	double dx, dy;
	double delta_x, delta_y;

	// Calcola la prima intersezione orizzontale
	if (ray->step_y > 0)
		y = floor(ray->y) + 1.0;
	else
		y = floor(ray->y);

	dy = y - ray->y;
	dx = dy * (ray->dir_x / ray->dir_y);
	x = ray->x + dx;

	// Calcola incremento per ciascun passo
	delta_y = ray->step_y * 1.0;
	delta_x = delta_y * (ray->dir_x / ray->dir_y);

	// Itera finché non colpisce un muro
	while (x >= 0 && x < map->dimension && y >= 0 && y < map->dimension)
	{
		int map_x = (int)(x);
		int map_y = (int)(y + (ray->step_y < 0 ? -1 : 0)); // lato corretto

		if (!not_wall(map_x, map_y, program))
		{
			hit->x = x;
			hit->y = y;
			return hypot(x - ray->x, y - ray->y);
		}
		x += delta_x;
		y += delta_y;
	}
	hit->x = x;
	hit->y = y;
	return INFINITY;
}
