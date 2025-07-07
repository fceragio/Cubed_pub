/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_blueprint_charmap_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:03:13 by federico          #+#    #+#             */
/*   Updated: 2025/07/07 15:04:34 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	spawns_ok(t_map_blueprint *blueprint)
{
	int	flag;
	int	i;
	int	j;

	if (blueprint == NULL || blueprint->char_map == NULL)
		return (FAILURE);
	flag = FAILURE;
	i = 0;
	while (blueprint->char_map[i])
	{
		j = 0;
		while (j < blueprint->x_len)
		{
			if (blueprint->char_map[i][j] == 'N'
				|| blueprint->char_map[i][j] == 'S'
				|| blueprint->char_map[i][j] == 'W'
				|| blueprint->char_map[i][j] == 'E')
			{
				if (flag == FAILURE)
					flag = SUCCESS;
				else
					return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (flag);
}

int	flood_fill(t_map_blueprint *blueprint, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= blueprint->x_len || y >= blueprint->y_len)
		return (FAILURE);
	if (map[y][x] == '\0')
		return (FAILURE);
	if (map[y][x] == '1')
		return (SUCCESS);
	if (map[y][x] == 'v')
		return (SUCCESS);
	map[y][x] = 'v';
	return (flood_fill(blueprint, map, x + 1, y)
			&& flood_fill(blueprint, map, x - 1, y)
			&& flood_fill(blueprint, map, x, y + 1)
			&& flood_fill(blueprint, map, x, y - 1));
}

int	map_is_closed(t_map_blueprint *blueprint)
{
	int	spawn_x;
	int	spawn_y;

	if (blueprint == NULL || blueprint->char_map == NULL)
		return (FAILURE);
	spawn_y = 0;
	while (blueprint->char_map[spawn_y])
	{
		spawn_x = 0;
		while(spawn_x < blueprint->x_len)
		{
			if (blueprint->char_map[spawn_y][spawn_x] == 'N'
				|| blueprint->char_map[spawn_y][spawn_x] == 'S'
				|| blueprint->char_map[spawn_y][spawn_x] == 'W'
				|| blueprint->char_map[spawn_y][spawn_x] == 'E')
				return (flood_fill(blueprint, blueprint->char_map, spawn_x, spawn_y));
			spawn_x++;
		}
		spawn_y++;
	}
	return (FAILURE);
}

int	blueprint_map_ok(t_map_blueprint *blueprint)
{
	if (spawns_ok(blueprint) == FAILURE)
	{
		print_error("Error\nWrong number of spawn points in the map\n");
		return (FAILURE);
	}
	if (map_is_closed(blueprint) == FAILURE)
	{
		print_error("Error\nMap is not properly closed by walls\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
