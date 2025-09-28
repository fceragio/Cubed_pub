/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:57:20 by federico          #+#    #+#             */
/*   Updated: 2025/09/28 17:57:51 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	is_hit_door(int x, int y, t_program *program)
{
	int	**map_2d_arr;

	map_2d_arr = program->map->arr;
	if (map_2d_arr[y][x] == 2)
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
