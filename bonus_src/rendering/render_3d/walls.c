/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:42:01 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/28 02:19:00 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	slice_init(t_slice *slice, t_ray *ray, t_program *program)
{
	int	slice_height;

	slice_height = (int)(WALL_SIZE / ray->perp_distance);
	slice->y0 = (WIN_HEIGHT - slice_height) / 2;
	slice->y1 = slice->y0 + slice_height;
	if (ray->door == true)
		slice->tex = program->map->door_texture;
	else
		slice->tex = select_tex_by_side(program->map, ray->wall_side);
	slice->tex_x = calc_tex_x(ray, slice->tex->width);
	slice->tex_step = (double)slice->tex->height / (double)slice_height;
	slice->y_start = slice->y0;
	if (slice->y_start < 0)
		slice->y_start = 0;
	slice->y_end = slice->y1;
	if (slice->y_end > WIN_HEIGHT)
		slice->y_end = WIN_HEIGHT;
	slice->tex_y = (slice->y_start - slice->y0) * slice->tex_step;
}

static void	draw_wall_slice(int col, t_ray *ray, t_program *program)
{
	t_slice	slice;
	int		color;

	slice_init(&slice, ray, program);
	while (slice.y_start < slice.y_end)
	{
		color = get_texture_pixel(slice);
		put_pixel(program, col, slice.y_start, color);
		slice.y_start++;
		slice.tex_y += slice.tex_step;
	}
}

void	draw_walls(t_program *program)
{
	int		i;
	int		x0;
	int		x1;
	int		x;
	t_ray	*ray;

	i = 0;
	while (i < NUM_RAYS)
	{
		x0 = WID_RAYS * i;
		x1 = x0 + WID_RAYS;
		if (x0 >= WIN_WIDTH)
			break ;
		ray = &program->player->fov[i];
		x = x0;
		while (x < x1 && x < WIN_WIDTH)
			draw_wall_slice(x++, ray, program);
		i++;
	}
	return ;
}
