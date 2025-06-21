/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:45:40 by federico          #+#    #+#             */
/*   Updated: 2025/06/22 01:35:03 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	put_pixel(t_program *program, int x, int y, int color)
{
	int	offset;

	offset = (y * program->line_len) + (x * program->bpp / 8);
	*(unsigned int *)(program->bit_addr + offset) = color;
}

// double	scale(double unscaled, double old_max, double new_min, double new_max)
// {
// 	double	scaled;

// 	scaled = (new_max - new_min) * (unscaled - OLD_MIN)
// 		/ (old_max - OLD_MIN) + new_min;
// 	return (scaled);
// }
