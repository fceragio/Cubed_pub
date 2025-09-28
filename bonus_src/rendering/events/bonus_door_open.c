/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_door_open.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:51:46 by federico          #+#    #+#             */
/*   Updated: 2025/09/28 19:31:48 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	try_open(t_point try, t_player *player, t_map *map)
{
	int	map_x;
	int	map_y;
	int	pl_x;
	int	pl_y;

	map_x = (int)try.x;
	map_y = (int)try.y;
	pl_x = (int)player->x;
	pl_y = (int)player->y;
	if (map_x < 0 || map_x >= map->x_dimension
		|| map_y < 0 || map_y >= map->y_dimension)
		return ;
	if (map_x == pl_x && map_y == pl_y)
		return ;
	if (map->arr[map_y][map_x] == DOOR)
		map->arr[map_y][map_x] = OPEN;
	else if (map->arr[map_y][map_x] == OPEN)
		map->arr[map_y][map_x] = DOOR;
}

void	door_interact(t_player *player, t_map *map)
{
	t_point	next;

	next.x = player->x + REACH;
	next.y = player->y;
	try_open(next, player, map);
	next.x = player->x - REACH;
	next.y = player->y;
	try_open(next, player, map);
	next.x = player->x;
	next.y = player->y + REACH;
	try_open(next, player, map);
	next.x = player->x;
	next.y = player->y - REACH;
	try_open(next, player, map);
}
