/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:24:23 by federico          #+#    #+#             */
/*   Updated: 2025/07/08 02:23:41 by federico         ###   ########.fr       */
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












t_map	*blueprint_to_map(t_map_blueprint *blueprint, void *mlx)
{
	return (NULL);
}
