/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:56:56 by federico          #+#    #+#             */
/*   Updated: 2025/09/28 18:40:31 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*map_init(void)
{
	t_map	*result;
	int		i;

	result = malloc(sizeof(t_map));
	if (result == NULL)
	{
		perror("map_init malloc");
		exit(EXIT_FAILURE);
	}
	result->arr = NULL;
	result->x_dimension = 0;
	result->y_dimension = 0;
	result->north_wall_texture = NULL;
	result->south_wall_texture = NULL;
	result->west_wall_texture = NULL;
	result->east_wall_texture = NULL;
	i = 0;
	while (i < DOOR_FILES)
	{
		result->door_arr[i] = NULL;
		i++;
	}
	result->door_texture = NULL;
	return (result);
}

void	destroy_texture(t_sprite *sprite)
{
	if (sprite->mlx_data.img)
		mlx_destroy_image(sprite->mlx_data.mlx, sprite->mlx_data.img);
	free(sprite);
	sprite = NULL;
}

static void	destroy_door_arr(t_map *map)
{
	int	i;

	i = 0;
	while (i < DOOR_FILES)
	{
		map->door_texture = map->door_arr[i];
		if (map->door_texture)
			destroy_texture(map->door_texture);
		i++;
	}
}

void	destroy_map(t_map *map)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (i < map->y_dimension)
	{
		free(map->arr[i]);
		i++;
	}
	free(map->arr);
	map->arr = NULL;
	if (map->north_wall_texture)
		destroy_texture(map->north_wall_texture);
	if (map->south_wall_texture)
		destroy_texture(map->south_wall_texture);
	if (map->west_wall_texture)
		destroy_texture(map->west_wall_texture);
	if (map->east_wall_texture)
		destroy_texture(map->east_wall_texture);
	destroy_door_arr(map);
	free(map);
}

int	sprite_init(t_sprite **result, void *mlx, char *path)
{
	(*result) = malloc(sizeof(t_sprite));
	if ((*result) == NULL)
	{
		perror("sprite init malloc");
		exit(EXIT_FAILURE);
	}
	(*result)->mlx_data.mlx = mlx;
	(*result)->mlx_data.win = NULL;
	(*result)->mlx_data.img = mlx_xpm_file_to_image(mlx,
			path, &(*result)->width, &(*result)->height);
	if ((*result)->mlx_data.img == NULL)
	{
		print_err("Error\nnot valid wall_texture\n");
		print_err(path);
		print_err("\n");
		return (FAILURE);
	}
	(*result)->mlx_data.bit_addr = mlx_get_data_addr((*result)->mlx_data.img,
			&(*result)->mlx_data.bpp,
			&(*result)->mlx_data.line_len, &(*result)->mlx_data.endian);
	if ((*result)->mlx_data.bit_addr == NULL)
	{
		exit(MLX_ERR);
	}
	return (SUCCESS);
}
