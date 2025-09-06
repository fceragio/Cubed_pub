/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_movement_turning.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:14:52 by federico          #+#    #+#             */
/*   Updated: 2025/09/02 00:59:50 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	turn_left(t_program *program)
{
	double	temp;

	temp = program->player->angle;
	program->player->angle = temp - SENSITIVITY;
	if (program->player->angle < 0)
		program->player->angle += 2 * M_PI;
}

void	turn_right(t_program *program)
{
	double	temp;

	temp = program->player->angle;
	program->player->angle = temp + SENSITIVITY;
	if (program->player->angle >= (2 * M_PI))
		program->player->angle = 0;
}

void	move_player(t_program *program)
{
	if (program->commands.w == YES)
		move_forward(program);
	if (program->commands.a == YES)
		move_left(program);
	if (program->commands.s == YES)
		move_backward(program);
	if (program->commands.d == YES)
		move_right(program);
	if (program->commands.l_arrow == YES)
		turn_left(program);
	if (program->commands.r_arrow == YES)
		turn_right(program);
	player_aim_init(program->player, program);
}
