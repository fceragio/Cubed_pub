/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:57:17 by federico          #+#    #+#             */
/*   Updated: 2025/09/09 20:46:26 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_array(t_map *map, t_list *list)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_dimension)
	{
		x = 0;
		while (list->content[x] && list->content[x] != '\n')
		{
			if (list->content[x] == '1')
				map->arr[y][x] = 1;
			else if (list->content[x] == '0')
				map->arr[y][x] = 0;
			else
				map->arr[y][x] = list->content[x];
			x++;
		}
		while (x < map->x_dimension)
		{
			map->arr[y][x] = M_SPACE;
			x++;
		}
		list = list->next;
		y++;
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
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < map->y_dimension)
	{
		map->arr[i] = malloc(sizeof(int) * map->x_dimension);
		if (map->arr[i] == NULL)
		{
			perror("set_map_array malloc");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	copy_array(map, blueprint->map_list);
}

int	set_map_colors(t_map *map, t_map_blueprint *blueprint)
{
	map->ceiling_color = (blueprint->c_vals[0] << 16) | (
			blueprint->c_vals[1] << 8) | blueprint->c_vals[2];
	map->floor_color = (blueprint->f_vals[0] << 16) | (
			blueprint->f_vals[1] << 8) | blueprint->f_vals[2];
	return (SUCCESS);
}

int	set_map_textures(t_map *map, t_map_blueprint *blueprint, void *mlx)
{
	if (sprite_init(&map->north_wall_texture, mlx, blueprint->no) == FAILURE)
		return (FAILURE);
	if (sprite_init(&map->south_wall_texture, mlx, blueprint->so) == FAILURE)
		return (FAILURE);
	if (sprite_init(&map->west_wall_texture, mlx, blueprint->we) == FAILURE)
		return (FAILURE);
	if (sprite_init(&map->east_wall_texture, mlx, blueprint->ea) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
