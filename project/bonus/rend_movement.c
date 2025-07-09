/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:11:44 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 01:15:11 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	move_forward(t_program *program)
{
	double	angle;
	double	tmp_x;
	double	tmp_y;

	angle = program->player->angle;
	tmp_x = program->player->x + safe_cos(angle) * SPEED;
	if (not_wall(tmp_x, program->player->y, program))
		program->player->x = tmp_x;
	tmp_y = program->player->y + safe_sin(angle) * SPEED;
	if (not_wall(program->player->x, tmp_y, program))
		program->player->y = tmp_y;
}

void	move_backward(t_program *program)
{
	double	angle;
	double	tmp_x;
	double	tmp_y;

	angle = program->player->angle;
	tmp_x = program->player->x - safe_cos(angle) * SPEED;
	if (not_wall(tmp_x, program->player->y, program))
		program->player->x = tmp_x;
	tmp_y = program->player->y - safe_sin(angle) * SPEED;
	if (not_wall(program->player->x, tmp_y, program))
		program->player->y = tmp_y;
}

void	move_left(t_program *program)
{
	double	angle;
	double	tmp_x;
	double	tmp_y;

	angle = program->player->angle;
	tmp_x = program->player->x + safe_sin(angle) * SPEED;
	if (not_wall(tmp_x, program->player->y, program))
		program->player->x = tmp_x;
	tmp_y = program->player->y - safe_cos(angle) * SPEED;
	if (not_wall(program->player->x, tmp_y, program))
		program->player->y = tmp_y;
}

void	move_right(t_program *program)
{
	double	angle;
	double	tmp_x;
	double	tmp_y;

	angle = program->player->angle;
	tmp_x = program->player->x - safe_sin(angle) * SPEED;
	if (not_wall(tmp_x, program->player->y, program))
		program->player->x = tmp_x;
	tmp_y = program->player->y + safe_cos(angle) * SPEED;
	if (not_wall(program->player->x, tmp_y, program))
		program->player->y = tmp_y;
}
