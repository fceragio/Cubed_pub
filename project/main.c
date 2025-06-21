/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:09 by federico          #+#    #+#             */
/*   Updated: 2025/06/22 02:55:19 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
	render_2d(&program);
	mlx_loop(program.mlx);

	return (0);
}

