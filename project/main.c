/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:09 by federico          #+#    #+#             */
/*   Updated: 2025/07/01 17:12:00 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
the map will always be formatted as a square, adding colums or lines of SPACEs where necessary.
this to semplify the logic.
*/

int main()
{
	t_map		map;
	t_player	player;
	t_program	program;

	program_init(&program, &map, &player);
	rendering(&program);

	return (1);
}

void	program_init(t_program *program, t_map *map, t_player *player)
{
	vs_init(program);
	map_init(map, program->mlx);
	program->map = map;
	player_init(player, *map, program);
	program->player = player;
}

void	rendering(t_program *program)
{
	commands_init(program);
	hook_handlers(program);
	mlx_loop_hook(program->mlx, loop_hook, program);
	mlx_loop(program->mlx);
}
