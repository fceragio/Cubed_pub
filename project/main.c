/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:09 by federico          #+#    #+#             */
/*   Updated: 2025/06/23 17:59:25 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
the map will always be formatted as a square, adding colums or lines of 0s where necessary.
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
	if (DEBUG_MODE)
		render_2d(program);
	// else
		// render_3d(program);
}