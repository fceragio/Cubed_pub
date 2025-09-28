/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:32:09 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/21 17:36:19 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	set_player_dir(char dir_chr)
{
	if (dir_chr == NORTH)
		return (3 * M_PI / 2);
	else if (dir_chr == SOUTH)
		return (M_PI / 2);
	else if (dir_chr == EAST)
		return (0);
	return (M_PI);
}

static int	set_player_position(t_player *player, t_map map, t_program *program)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.y_dimension)
	{
		x = 0;
		while (x < map.x_dimension)
		{
			if (map.arr[y][x] == NORTH || map.arr[y][x] == SOUTH
				|| map.arr[y][x] == WEST || map.arr[y][x] == EAST)
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				player->angle = set_player_dir(map.arr[y][x]);
				program->player_cnt++;
			}
			x++;
		}
		y++;
	}
	if (program->player_cnt != 1)
		return (print_err(ERR_HEAD), print_err(INVALID_PLAYER_NUM), FAILURE);
	return (SUCCESS);
}

int	player_init(t_player *player, t_map map, t_program *program)
{
	if (set_player_position(player, map, program) == FAILURE)
	{
		program->exit_status = PLAYER_ERR;
		return (FAILURE);
	}
	program->player = player;
	set_rays(player, program);
	return (SUCCESS);
}
