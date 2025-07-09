/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_movement_turning.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:14:52 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 01:15:16 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
