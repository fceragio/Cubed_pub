/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:24:23 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 02:16:46 by federico         ###   ########.fr       */
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
	close(fd);
	return (create_map(&map_blueprint, mlx));
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
		}
		next_line = get_next_line(fd);
	}
	while (next_line)
	{
		if (assign_map_line(next_line, *blueprint) == FAILURE)
		{
			clear_nextlines(fd);
			clear_blueprint(blueprint);
		}
		next_line = get_next_line(fd);
	}
}

t_map	*create_map(t_map_blueprint **blueprint, void *mlx)
{
	t_map	*map;

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

t_map	*blueprint_to_map(t_map_blueprint *blueprint, void *mlx)
{
	t_map	*result;

	result = map_init();
	if (set_map_textures(result, blueprint, mlx) == FAILURE)
	{
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
