/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:41:59 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/21 17:14:31 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_pixel(t_slice slice)
{
	char		*pixel;
	t_sprite	*texture;
	int			tex_x;
	int			tex_y;

	texture = slice.tex;
	tex_x = (int)slice.tex_x;
	tex_y = (int)slice.tex_y;
	if (tex_x < 0 || tex_x >= texture->width
		|| tex_y < 0 || tex_y >= texture->height)
		return (ERROR_COLOR);
	pixel = texture->mlx_data.bit_addr + (tex_y
			* texture->mlx_data.line_len + tex_x * texture->mlx_data.bpp / 8);
	return (*(int *)pixel);
}

t_sprite	*select_tex_by_side(t_map *map, int side)
{
	if (side == NORTH)
		return (map->north_wall_texture);
	if (side == SOUTH)
		return (map->south_wall_texture);
	if (side == EAST)
		return (map->east_wall_texture);
	return (map->west_wall_texture);
}

int	calc_tex_x(t_ray *ray, int tex_w)
{
	int	raw;
	int	wx;

	if (ray->wall_side == NORTH || ray->wall_side == SOUTH)
		raw = (int)(ray->hit_x * WALL_SIZE);
	else
		raw = (int)(ray->hit_y * WALL_SIZE);
	wx = raw % WALL_SIZE;
	if (wx < 0)
		wx += WALL_SIZE;
	if (ray->wall_side == NORTH || ray->wall_side == EAST)
		wx = WALL_SIZE - wx - 1;
	return ((wx * tex_w) / WALL_SIZE);
}
