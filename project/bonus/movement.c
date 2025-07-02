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
