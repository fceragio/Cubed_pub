/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:05:06 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 18:46:18 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	hook_handlers(t_program *program)
{
	mlx_hook(program->mlx_data.win, DestroyNotify,
		StructureNotifyMask, red_x_press_handling, program);
	mlx_hook(program->mlx_data.win, VisibilityNotify,
		VisibilityChangeMask, visibility_handling, program);
	mlx_hook(program->mlx_data.win, KeyPress, KeyPressMask,
		key_press_handling, program);
}

int	red_x_press_handling(t_program *program)
{
	program_close(program, SUCCESS);
	return (SUCCESS);
}

int	visibility_handling(t_program *program)
{
	render(program);
	return (SUCCESS);
}

int	key_press_handling(int keysym, t_program *program)
{
	if (keysym == XK_Escape)
		program_close(program, SUCCESS);
	if (keysym == XK_w)
		move_forward(program);
	if (keysym == XK_a)
		move_left(program);
	if (keysym == XK_s)
		move_backward(program);
	if (keysym == XK_d)
		move_right(program);
	if (keysym == XK_Left)
		turn_left(program);
	if (keysym == XK_Right)
		turn_right(program);
	player_aim_init(program->player, program);
	render(program);
	return (SUCCESS);
}
