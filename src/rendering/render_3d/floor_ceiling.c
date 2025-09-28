/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:41:55 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/21 17:13:59 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_program *program)
{
	int	mid_win_height;
	int	y;
	int	x;

	mid_win_height = WIN_HEIGHT / 2;
	y = 0;
	while (y < mid_win_height)
	{
		x = 0;
		while (x < WIN_WIDTH)
			put_pixel(program, x++, y, program->map->ceiling_color);
		y++;
	}
	y = mid_win_height;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
			put_pixel(program, x++, y, program->map->floor_color);
		y++;
	}
}
