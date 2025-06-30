/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:45:40 by federico          #+#    #+#             */
/*   Updated: 2025/06/26 19:42:33 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	put_pixel(t_program *program, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	offset = (y * program->line_len) + (x * program->bpp / 8);
	*(unsigned int *)(program->bit_addr + offset) = color;
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
	if (total_us >= U_FPS)
	{
		update_player(program);
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

void	update_player(t_program *program)
{
	if (program->commands.w == true)
		move_forward(program);
	if (program->commands.a == true)
		move_left(program);
	if (program->commands.s == true)
		move_backward(program);
	if (program->commands.d == true)
		move_right(program);
	if (program->commands.l_arrow == true)
		turn_left(program);
	if (program->commands.r_arrow == true)
		turn_right(program);
	player_aim_init(program->player, program);
}
