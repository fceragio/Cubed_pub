/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:09 by federico          #+#    #+#             */
/*   Updated: 2025/07/08 17:01:15 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
the map will always be formatted as a square, adding colums or lines of SPACEs where necessary.
this to semplify the logic.
*/

int main(int argc, char **argv)
{
	void		*mlx;
	t_map		*map;
	t_player	player;
	t_program	program;

	mlx = mlx_init();
	if (mlx == NULL)
		exit(MLX_ERR);
	map = parsing(argc, argv[1], mlx);
	if (map == NULL)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return (3);
	}
	program_init(mlx, &program, map, &player);
	rendering(&program);

	return (3);
}

void	program_init(void *mlx, t_program *program, t_map *map, t_player *player)
{
	vs_init(mlx, program);
	program->map = map;
	player_init(player, *map, program);
	program->player = player;
}

void	rendering(t_program *program)
{
	commands_init(program);
	hook_handlers(program);
	mlx_loop_hook(program->mlx_data.mlx, loop_hook, program);
	mlx_loop(program->mlx_data.mlx);
}
