/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_seup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:39:37 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/12 20:05:11 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray_init(t_ray *ray, double *angle, t_program *program)
{
	wrap_angle(angle);
	ray->x = program->player->x;
	ray->y = program->player->y;
	ray->angle = *angle;
	ray->dir_x = safe_cos(*angle);
	ray->dir_y = safe_sin(*angle);
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	ray->distance = find_distance_to_wall(ray, program);
	ray->perp_distance = ray->distance
		* safe_cos(ray->angle - program->player->angle);
	ray->hit_x = ray->x + ray->distance * ray->dir_x;
	ray->hit_y = ray->y + ray->distance * ray->dir_y;
}

void	set_rays(t_player *player, t_program *program)
{
	int		i;
	double	angle;
	double	angle_step;

	ray_init(&player->aim, &(player->angle), program);
	angle = player->angle - (FOV / 2.0);
	angle_step = FOV / ((double)NUM_RAYS - 1);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_init(&player->fov[i], &angle, program);
		angle += angle_step;
		i++;
	}
}
