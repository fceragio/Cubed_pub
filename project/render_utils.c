/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:45:40 by federico          #+#    #+#             */
/*   Updated: 2025/06/26 19:42:33 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	put_pixel(t_program *program, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	offset = (y * program->line_len) + (x * program->bpp / 8);
	*(unsigned int *)(program->bit_addr + offset) = color;
}
