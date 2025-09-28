/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:58:50 by federico          #+#    #+#             */
/*   Updated: 2025/09/28 03:29:43 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_empty_2d(int i, int j, t_program *program)
{
	int	x;
	int	y;
	int	x_end;
	int	y_end;

	x_end = i + TILE_SIZE;
	y_end = j + TILE_SIZE;
	x = i;
	while (x < x_end)
	{
		y = j;
		while (y < y_end)
		{
			put_pixel(program, x, y, EMPTY);
			y++;
		}
		x++;
	}
}

void	put_wall_2d(int i, int j, t_program *program)
{
	int	x;
	int	y;
	int	x_end;
	int	y_end;

	x_end = i + TILE_SIZE;
	y_end = j + TILE_SIZE;
	x = i;
	while (x < x_end)
	{
		y = j;
		while (y < y_end)
		{
			put_pixel(program, x, y, WALL);
			y++;
		}
		x++;
	}
}

void	put_door_2d(int i, int j, t_program *program)
{
	int	x;
	int	y;
	int	x_end;
	int	y_end;

	x_end = i + TILE_SIZE;
	y_end = j + TILE_SIZE;
	x = i;
	while (x < x_end)
	{
		y = j;
		while (y < y_end)
		{
			put_pixel(program, x, y, BLACK);
			y++;
		}
		x++;
	}
}
