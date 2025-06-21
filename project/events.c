/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:05:06 by federico          #+#    #+#             */
/*   Updated: 2025/06/22 01:19:13 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	hook_handlers(t_program *program)
{
	mlx_hook(program->win, DestroyNotify, StructureNotifyMask, red_x_press_handling, program);
	mlx_hook(program->win, KeyPress, KeyPressMask, key_press_handling, program);
}

int	red_x_press_handling(t_program *program)
{
	program_close(program, SUCCESS);
	return (SUCCESS);
}

int	key_press_handling(int keysym, t_program *program)
{
	if (keysym == XK_Escape)
		program_close(program, SUCCESS);
	else
		return (FAILURE);
	return (SUCCESS);
}
