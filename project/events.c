/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:05:06 by federico          #+#    #+#             */
/*   Updated: 2025/06/29 01:20:00 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	hook_handlers(t_program *program)
{
	mlx_hook(program->win, DestroyNotify, StructureNotifyMask, red_x_press_handling, program);
	mlx_hook(program->win, VisibilityNotify, VisibilityChangeMask, visibility_handling, program);
	mlx_hook(program->win, KeyPress, KeyPressMask, key_press_handling, program);
}

int	red_x_press_handling(t_program *program)
{
	program_close(program, SUCCESS);
	return (SUCCESS);
}

int	visibility_handling(t_program *program)
{
	(void)program;
	return (SUCCESS);
}

int	key_press_handling(int keysym, t_program *program)
{
	if (keysym == XK_Escape)
		program_close(program, SUCCESS);
	else if (keysym == XK_Left || keysym == XK_Right)
		turn_pov(keysym, program);
	else if (keysym == XK_w || keysym == XK_a
		|| keysym == XK_s || keysym == XK_d)
		move_pov(keysym, program);
	else
		return (FAILURE);
	return (SUCCESS);
}

void	move_pov(int keysym, t_program *program)
{
	if (keysym == XK_w)
		move_forward(program);
	else if (keysym == XK_s)
		move_backward(program);
	else if (keysym == XK_a)
		move_left(program);
	else if (keysym == XK_d)
		move_right(program);
	player_aim_init(program->player, program);
}

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

void	turn_pov(int keysym, t_program *program)
{
	if (keysym == XK_Left)
		turn_left(program);
	else
		turn_right(program);
	player_aim_init(program->player, program);
}

void	turn_left(t_program *program)
{
	double	temp;

	temp = program->player->angle;
	program->player->angle = temp - M_PI / 16;
	if (program->player->angle < 0)
		program->player->angle += 2 * M_PI;
}

void	turn_right(t_program *program)
{
	double	temp;

	temp = program->player->angle;
	program->player->angle = temp + M_PI / 16;
	if (program->player->angle >= (2 * M_PI))
		program->player->angle = 0;
}
