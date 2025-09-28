/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:36:08 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/26 16:04:12 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_left(t_program *program)
{
	double	tmp;

	tmp = program->player->angle;
	program->player->angle = tmp - SENSITIVITY;
	if (program->player->angle < 0)
		program->player->angle += 2 * M_PI;
	return ;
}

void	turn_right(t_program *program)
{
	double	tmp;

	tmp = program->player->angle;
	program->player->angle = tmp + SENSITIVITY;
	if (program->player->angle >= (2 * M_PI))
		program->player->angle = 0;
	return ;
}
