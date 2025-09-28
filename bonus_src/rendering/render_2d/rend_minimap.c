/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:58:40 by federico          #+#    #+#             */
/*   Updated: 2025/09/28 18:26:51 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rend2d_loop(t_point *map_p, t_point *pixel,
			t_map *map, t_program *program)
{
	map_p->y = 0;
	while (pixel->y < (WIN_HEIGHT - TILE_SIZE))
	{
		if (map->arr[(int)map_p->y][(int)map_p->x] == 1)
			put_wall_2d(pixel->x, pixel->y, program);
		else if (map->arr[(int)map_p->y][(int)map_p->x] == 2
			|| map->arr[(int)map_p->y][(int)map_p->x] == 3)
			put_door_2d(pixel->x, pixel->y, program);
		else if (map->arr[(int)map_p->y][(int)map_p->x] != M_SPACE)
			put_empty_2d(pixel->x, pixel->y, program);
		pixel->y += TILE_SIZE;
		map_p->y++;
	}
	pixel->x += TILE_SIZE;
	map_p->x++;
}

static void	render_2d_map(t_map *map, t_program *program)
{
	t_point	start;
	t_point	map_p;
	t_point	pixel;

	start.x = WIN_WIDTH - (TILE_SIZE * (map->x_dimension + 1));
	start.y = WIN_HEIGHT - (TILE_SIZE * (map->y_dimension + 1));
	map_p.x = 0;
	map_p.y = 0;
	pixel.x = start.x;
	while (pixel.x < (WIN_WIDTH - TILE_SIZE))
	{
		pixel.y = start.y;
		rend2d_loop(&map_p, &pixel, map, program);
	}
}

static void	render_2d_player(t_player *player, t_program *program)
{
	t_point	start;
	t_point	end;
	t_point	pixel;

	start.x = player->x * TILE_SIZE + WIN_WIDTH
		- (TILE_SIZE * (program->map->x_dimension + 1)) - 1;
	start.y = player->y * TILE_SIZE + WIN_HEIGHT
		- (TILE_SIZE * (program->map->y_dimension + 1)) - 1;
	end.x = start.x + 2;
	end.y = start.y + 2;
	while (start.x <= end.x)
	{
		pixel.y = start.y;
		while (pixel.y <= end.y)
		{
			put_pixel(program, start.x, pixel.y, PLAYER);
			pixel.y++;
		}
		start.x++;
	}
}

void	render_2d(t_program *program)
{
	render_2d_map(program->map, program);
	render_2d_player(program->player, program);
}
