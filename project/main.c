/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:09 by federico          #+#    #+#             */
/*   Updated: 2025/06/29 01:23:09 by federico         ###   ########.fr       */
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

	program_init(&program);
	map_init(&map);
	program.map = &map;
	player_init(&player, map, &program);
	program.player = &player;
	hook_handlers(&program);
	render(&program);
	mlx_loop(program.mlx);

	return (0);
}

void	render(t_program *program)
{
	render_3d(program);
	if (DEBUG_MODE)
		render_2d(program);
}
