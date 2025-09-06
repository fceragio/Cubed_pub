/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:45:40 by federico          #+#    #+#             */
/*   Updated: 2025/09/02 00:58:41 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	put_pixel(t_program *program, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	offset = (y * program->mlx_data.line_len) + (x * program->mlx_data.bpp / 8);
	*(unsigned int *)(program->mlx_data.bit_addr + offset) = color;
}

void	render(t_program *program)
{
	program->rendered = NO;
	if (DEBUG_MODE)
		render_2d(program);
	else
		render_3d(program);
	mlx_put_image_to_window(program->mlx_data.mlx,
		program->mlx_data.win, program->mlx_data.img, MLX_DEFAULT, MLX_DEFAULT);
	program->rendered = YES;
}

int	rend_loop(t_program *program)
{
	move_player(program);
	if (program->rendered == YES)
		render(program);
	return (SUCCESS);
}
