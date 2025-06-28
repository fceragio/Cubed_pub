/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:09 by federico          #+#    #+#             */
/*   Updated: 2025/06/28 15:22:04 by federico         ###   ########.fr       */
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

	map_init(&map);
	player_init(&player, map);
	program.map = &map;
	program.player = &player;
	program_init(&program);
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
