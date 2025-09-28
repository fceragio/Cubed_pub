/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:36:07 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/28 01:39:16 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	can_move(double x, double y, t_program *program)
{
	int	int_x;
	int	int_y;

	int_x = (int)x;
	int_y = (int)y;
	if (is_out_of_bounds(int_x, int_y, program)
		|| is_hit_wall(int_x, int_y, program)
		|| is_hit_door(int_x, int_y, program))
		return (false);
	return (true);
}

void	step_left(t_program *program)
{
	double		angle;
	t_point		p;

	angle = program->player->angle;
	p.x = program->player->x + safe_sin(angle) * SPEED;
	if (can_move(p.x, program->player->y, program))
		program->player->x = p.x;
	p.y = program->player->y - safe_cos(angle) * SPEED;
	if (can_move(program->player->x, p.y, program))
		program->player->y = p.y;
}

void	step_forward(t_program *program)
{
	double		angle;
	t_point		p;

	angle = program->player->angle;
	p.x = program->player->x + safe_cos(angle) * SPEED;
	if (can_move(p.x, program->player->y, program))
		program->player->x = p.x;
	p.y = program->player->y + safe_sin(angle) * SPEED;
	if (can_move(program->player->x, p.y, program))
		program->player->y = p.y;
}

void	step_right(t_program *program)
{
	double		angle;
	t_point		p;

	angle = program->player->angle;
	p.x = program->player->x - safe_sin(angle) * SPEED;
	if (can_move(p.x, program->player->y, program))
		program->player->x = p.x;
	p.y = program->player->y + safe_cos(angle) * SPEED;
	if (can_move(program->player->x, p.y, program))
		program->player->y = p.y;
}

void	step_backward(t_program *program)
{
	double		angle;
	t_point		p;

	angle = program->player->angle;
	p.x = program->player->x - safe_cos(angle) * SPEED;
	if (can_move(p.x, program->player->y, program))
		program->player->x = p.x;
	p.y = program->player->y - safe_sin(angle) * SPEED;
	if (can_move(program->player->x, p.y, program))
		program->player->y = p.y;
}
