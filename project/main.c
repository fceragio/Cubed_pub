/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:09 by federico          #+#    #+#             */
/*   Updated: 2025/06/29 02:08:53 by federico         ###   ########.fr       */
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
	rendering(&program);

	return (1);
}

void	rendering(t_program *program)
{
	hook_handlers(program);
	mlx_loop_hook(program->mlx, loop_hook, program);
	mlx_loop(program->mlx);
}

void	render(t_program *program)
{
	if (DEBUG_MODE)
		render_2d(program);
	else
		render_3d(program);
	mlx_put_image_to_window(program->mlx, program->win, program->img, MLX_DEFAULT, MLX_DEFAULT);
}

int	loop_hook(t_program *program)
{
	static struct timeval	last = {0, 0};
	struct timeval			current;
	long					total_us;

	gettimeofday(&current, NULL);
	if (last.tv_sec == 0 && last.tv_usec == 0)
	{
		last = current;
		return (0);
	}
	total_us = (current.tv_sec - last.tv_sec) * U_SEC + (current.tv_usec - last.tv_usec);
	// if (total_us >= U_FPS)
	// {
	// 	render(program);
	// 	last = current;
	// }
	if (total_us >= U_FPS)
	{
    	render(program);
		last.tv_usec += U_FPS;
    	while (last.tv_usec >= U_SEC)
    	{
        	last.tv_usec -= U_SEC;
        	last.tv_sec += 1;
    	}
	}
	return (0);
}
