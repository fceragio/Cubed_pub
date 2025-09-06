/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:05:06 by federico          #+#    #+#             */
/*   Updated: 2025/09/02 01:01:55 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	hook_handlers(t_program *program)
{
	mlx_hook(program->mlx_data.win, DestroyNotify,
		StructureNotifyMask, red_x_press_handling, program);
	mlx_hook(program->mlx_data.win, VisibilityNotify,
		VisibilityChangeMask, visibility_handling, program);
	mlx_hook(program->mlx_data.win, KeyPress, KeyPressMask,
		key_press_handling, program);
	mlx_hook(program->mlx_data.win, KeyRelease, KeyReleaseMask,
		key_release_handling, program);
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
		program->commands.w = YES;
	if (keysym == XK_a)
		program->commands.a = YES;
	if (keysym == XK_s)
		program->commands.s = YES;
	if (keysym == XK_d)
		program->commands.d = YES;
	if (keysym == XK_Left)
		program->commands.l_arrow = YES;
	if (keysym == XK_Right)
		program->commands.r_arrow = YES;
	return (SUCCESS);
}

int	key_release_handling(int keysym, t_program *program)
{
	if (keysym == XK_w)
		program->commands.w = NO;
	if (keysym == XK_a)
		program->commands.a = NO;
	if (keysym == XK_s)
		program->commands.s = NO;
	if (keysym == XK_d)
		program->commands.d = NO;
	if (keysym == XK_Left)
		program->commands.l_arrow = NO;
	if (keysym == XK_Right)
		program->commands.r_arrow = NO;
	return (SUCCESS);
}
