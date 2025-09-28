/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:37:43 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/23 11:18:39 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_program *program)
{
	if (program->commands.a == true)
		step_left(program);
	if (program->commands.w == true)
		step_forward(program);
	if (program->commands.d == true)
		step_right(program);
	if (program->commands.s == true)
		step_backward(program);
	if (program->commands.l_arrow == true)
		turn_left(program);
	if (program->commands.r_arrow == true)
		turn_right(program);
	set_rays(program->player, program);
	return ;
}
