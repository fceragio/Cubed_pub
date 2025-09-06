/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:58:40 by federico          #+#    #+#             */
/*   Updated: 2025/09/01 19:39:14 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	render_2d(t_program *program)
{
	render_2d_map(program->map, program);
	render_2d_player(program->player, program);
	render_2d_rays(program->player, program);
}

void	render_2d_map(t_map *map, t_program *program)
{
	int	x;
	int	y;

	reset_2d(program);
	x = 0;
	while (x < map->x_dimension)
	{
		y = 0;
		while (y < map->y_dimension)
		{
			if (map->arr[y][x] == 1)
				put_wall_2d(x, y, program);
			else if (map->arr[y][x] != M_SPACE)
				put_empty_2d(x, y, program);
			y++;
		}
		x++;
	}
}

void	render_2d_player(t_player *player, t_program *program)
{
	int	i;
	int	j;

	i = -1;
	while (i < 2)
	{
		j = -1;
		while (j < 2)
		{
			put_pixel(program, player->x * TILE_SIZE + i,
				player->y * TILE_SIZE + j, PLAYER);
			j++;
		}
		i++;
	}
}

void	render_2d_rays(t_player *player, t_program *program)
{
	int		i;

	i = 0;
	render_2d_ray(player->aim, program, AIM);
	while (i < NUM_RAYS)
	{
		render_2d_ray(player->fov[i], program, RAY);
		i++;
	}
}
