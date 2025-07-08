/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:57:17 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 02:30:44 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	copy_array(t_map *map, t_list *list)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_dimension)
	{
		x = 0;
		while (x < map->x_dimension)
		{
			if (list->content[x] == '1')
				map->arr[y][x] = 1;
			else if (list->content[x] == '0')
				map->arr[y][x] = 0;
			else if (list->content[x] == '\0' || list->content[x] == '\n')
				map->arr[y][x] = M_SPACE;
			else
				map->arr[y][x] = list->content[x];
			printf("%d ", map->arr[y][x]);
			x++;
		}
		list = list->next;
		y++;
		printf("\n");
	}
}

void	set_map_array(t_map *map, t_map_blueprint *blueprint)
{
	int	i;

	map->x_dimension = blueprint->x_len;
	map->y_dimension = blueprint->y_len;
	map->arr = malloc(sizeof(int *) * map->y_dimension);
	if (map->arr == NULL)
	{
		perror("set_map_array malloc");
		exit(1);
	}
	i = 0;
	while (i < map->y_dimension)
	{
		map->arr[i] = malloc(sizeof(int) * map->x_dimension);
		if (map->arr[i] == NULL)
		{
			perror("set_map_array malloc");
			exit(1);
		}
		i++;
	}
	copy_array(map, blueprint->map_list);
}

int	set_map_colors(t_map *map, t_map_blueprint *blueprint)
{
	map->sealing_color = (blueprint->C_vals[0] << 16) | (
			blueprint->C_vals[1] << 8) | blueprint->C_vals[2];
	map->floor_color = (blueprint->F_vals[0] << 16) | (
			blueprint->F_vals[1] << 8) | blueprint->F_vals[2];
	return (SUCCESS);
}

int	set_map_textures(t_map *map, t_map_blueprint *blueprint, void *mlx)
{
	if (sprite_init(&map->north_wall_texture, mlx, blueprint->No) == FAILURE)
		return (FAILURE);
	if (sprite_init(&map->south_wall_texture, mlx, blueprint->So) == FAILURE)
		return (FAILURE);
	if (sprite_init(&map->west_wall_texture, mlx, blueprint->We) == FAILURE)
		return (FAILURE);
	if (sprite_init(&map->east_wall_texture, mlx, blueprint->Ea) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
