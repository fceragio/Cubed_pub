/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:21:34 by federico          #+#    #+#             */
/*   Updated: 2025/07/02 19:41:55 by federico         ###   ########.fr       */
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

double	find_vertical_hit_distance(t_ray *ray, t_map *map, t_point *hit, t_program *program)
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

double	find_horizontal_hit_distance(t_ray *ray, t_map *map, t_point *hit, t_program *program)
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
