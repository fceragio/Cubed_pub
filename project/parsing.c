/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:24:23 by federico          #+#    #+#             */
/*   Updated: 2025/07/08 16:54:26 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_map	*parsing(int argc, char *file_path, void *mlx)
{
	t_map_blueprint	*map_blueprint;
	int				fd;

	if (cub_file_is_ok(argc, file_path) == FAILURE)
		return (NULL);
	map_blueprint = malloc(sizeof(t_map_blueprint));
	if (map_blueprint == NULL)
	{
		perror("parsing malloc");
		exit(1);
	}
	fd = open(file_path, O_RDONLY, 0);
	create_map_blueprint(&map_blueprint, fd);
	printf("closing fd\n");
	close(fd);
	return (create_map(&map_blueprint, mlx));
}

t_map	*create_map(t_map_blueprint **blueprint, void *mlx)
{
	t_map	*map;

	printf("blueprint->%p\n", *blueprint);
	if (*blueprint == NULL)
		return (NULL);
	if (blueprint_ok(*blueprint) == FAILURE)
	{
		clear_blueprint(blueprint);
		return (NULL);
	}
	map = blueprint_to_map(*blueprint, mlx);
	clear_blueprint(blueprint);
	return (map);
}

void	create_map_blueprint(t_map_blueprint **blueprint, int fd)
{
	char	*next_line;

	blueprint_init(*blueprint);
	next_line = get_next_line(fd);
	while (next_line)
	{
		if (identify_line(next_line) == M_MAP)
			break ;
		if (assign_line(next_line, *blueprint) == FAILURE)
		{
			clear_nextlines(fd);
			clear_blueprint(blueprint);
			return ;
		}
		next_line = get_next_line(fd);
	}
	while (next_line)
	{
		if (assign_map_line(next_line, *blueprint) == FAILURE)
		{
			clear_nextlines(fd);
			clear_blueprint(blueprint);
			return ;
		}
		next_line = get_next_line(fd);
	}
}

int	blueprint_ok(t_map_blueprint *blueprint)
{
	printf("entering blueprint_ok\n");
	if (blueprint->No_flag == false || blueprint->So_flag == false
		|| blueprint->We_flag == false || blueprint->Ea_flag == false
		|| blueprint->C_flag == false || blueprint->F_flag == false)
	{
		print_error("Error\nThe file didn't contain all the fields required\n");
		return (FAILURE);
	}
	create_char_map(blueprint);
	if (blueprint_map_ok(blueprint) == FAILURE)
		return (FAILURE);
	blueprint_prepare_fields(blueprint);
	return (SUCCESS);
}










t_map	*map_init(void)
{
	t_map	*result;

	result = malloc(sizeof(t_map));
	if (result == NULL)
	{
		perror("map_init malloc");
		exit(1);
	}
	result->arr = NULL;
	result->x_dimension = 0;
	result->y_dimension = 0;
	result->sealing_color = 0;
	result->floor_color = 0;
	result->north_wall_texture = NULL;
	result->south_wall_texture = NULL;
	result->west_wall_texture = NULL;
	result->east_wall_texture = NULL;
	return (result);
}
void	destroy_texture(t_sprite *sprite)
{
	printf("destroying texture\n");
	if (sprite->mlx_data.img)
		mlx_destroy_image(sprite->mlx_data.mlx, sprite->mlx_data.img);
	free(sprite);
	sprite = NULL;
}
void	destroy_map(t_map *map)
{
	printf("destroy_map\n");
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
	printf("destroy_map\n");
	if (map->north_wall_texture)
		destroy_texture(map->north_wall_texture);
	map->north_wall_texture = NULL;
	if (map->south_wall_texture)
		destroy_texture(map->south_wall_texture);
	map->south_wall_texture = NULL;
	if (map->west_wall_texture)
		destroy_texture(map->west_wall_texture);
	map->west_wall_texture = NULL;
	if (map->east_wall_texture)
		destroy_texture(map->east_wall_texture);
	map->east_wall_texture = NULL;
	printf("destroy_map\n");
	free(map);
}






int	sprite_init(t_sprite **result, void *mlx, char *path)
{
	(*result) = malloc(sizeof(t_sprite));
	if ((*result) == NULL)
	{
		perror("sprite init malloc");
		exit(1);
	}
	(*result)->mlx_data.mlx = mlx;
	(*result)->mlx_data.win = NULL;
	(*result)->mlx_data.img = mlx_xpm_file_to_image(mlx, path, &(*result)->width, &(*result)->height);
	if ((*result)->mlx_data.img == NULL)
	{
		print_error("Error\nnot valid wall_texture\n");
		print_error(path);
		print_error("\n");
		return (FAILURE);
	}
	(*result)->mlx_data.bit_addr = mlx_get_data_addr((*result)->mlx_data.img, &(*result)->mlx_data.bpp, &(*result)->mlx_data.line_len, &(*result)->mlx_data.endian);
	if ((*result)->mlx_data.bit_addr == NULL)
	{
		exit(MLX_ERR);
	}
	printf("sprite ok\n");
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
	//yet to implement
	map->sealing_color = SEALING;
	map->floor_color = FLOOR;
	return (SUCCESS);
}

t_map	*blueprint_to_map(t_map_blueprint *blueprint, void *mlx)
{
	t_map	*result;

	result = map_init();
	if (set_map_textures(result, blueprint, mlx) == FAILURE)
	{
		printf("set_map_textures failed\n\n");
		destroy_map(result);
		return (NULL);
	}
	if (set_map_colors(result, blueprint) == FAILURE)
	{
		print_error("Error\ninvalid color values in .cub\n");
		destroy_map(result);
		return (NULL);
	}
	set_map_array(result, blueprint);
	return (result);
}
