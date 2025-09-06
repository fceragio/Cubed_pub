/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_inits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:28:17 by federico          #+#    #+#             */
/*   Updated: 2025/09/01 19:39:07 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	set_player_position(t_player *player, t_map map)
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
				player->angle = map.arr[y][x];
			}
			x++;
		}
		y++;
	}
}

void	player_init(t_player *player, t_map map, t_program *program)
{
	set_player_position(player, map);
	if (player->angle == NORTH)
		player->angle = 3 * M_PI / 2;
	if (player->angle == SOUTH)
		player->angle = M_PI / 2;
	if (player->angle == EAST)
		player->angle = 0;
	if (player->angle == WEST)
		player->angle = M_PI;
	player_aim_init(player, program);
}

void	player_aim_init(t_player *player, t_program *program)
{
	int		i;
	double	angle;
	double	angle_step;

	ray_init(&player->aim, player, player->angle, program);
	angle = player->angle - (FOV / 2.0);
	angle_step = FOV / ((double)NUM_RAYS - 1);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_init(&player->fov[i], player, angle, program);
		angle += angle_step;
		i++;
	}
}

void	ray_init(t_ray *ray, t_player *player, double angle, t_program *program)
{
	safe_angle(&angle);
	ray->x = player->x;
	ray->y = player->y;
	ray->angle = angle;
	ray->dir_x = safe_cos(angle);
	ray->dir_y = safe_sin(angle);
	if (ray->dir_x > 0)
		ray->step_x = +1;
	else
		ray->step_x = -1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = +1;
	ray->wall_side = find_wall_distance(&ray->len, ray, program->map, program);
	ray->distance = ray->len * safe_cos(ray->angle - player->angle);
}
