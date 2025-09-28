/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:06:19 by federico          #+#    #+#             */
/*   Updated: 2025/09/28 17:53:41 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	turn_mouse_left(int diff, t_program *program)
{
	double	tmp;

	tmp = program->player->angle;
	program->player->angle = tmp + (diff * MOUSE_SENSITIVITY);
	if (program->player->angle < 0)
		program->player->angle += 2 * M_PI;
	return ;
}

static void	turn_mouse_right(int diff, t_program *program)
{
	double	tmp;

	tmp = program->player->angle;
	program->player->angle = tmp + (diff * MOUSE_SENSITIVITY);
	if (program->player->angle >= (2 * M_PI))
		program->player->angle = 0;
	return ;
}

int	mouse_movement(int x, int y, t_program *program)
{
	static int	old_mouseloc = WIN_WIDTH / 2;
	int			diff;

	if (program->block_mouse == false)
		return (FAILURE);
	(void)y;
	diff = x - old_mouseloc;
	if (diff > 0)
	{
		turn_mouse_left(diff, program);
	}
	if (diff < 0)
	{
		turn_mouse_right(diff, program);
	}
	mlx_mouse_move(program->mlx_data.mlx, program->mlx_data.win,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (SUCCESS);
}

void	bonus_press_handling(int keysym, t_program *program)
{
	if (keysym == XK_m && program->rend_map == true)
		program->rend_map = false;
	else if (keysym == XK_m && program->rend_map == false)
		program->rend_map = true;
	if (keysym == XK_p && program->block_mouse == true)
		program->block_mouse = false;
	else if (keysym == XK_p && program->block_mouse == false)
		program->block_mouse = true;
	if (keysym == XK_space)
		door_interact(program->player, program->map);
}
