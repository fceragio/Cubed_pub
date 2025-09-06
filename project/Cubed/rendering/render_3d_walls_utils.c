/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_walls_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:32:25 by federico          #+#    #+#             */
/*   Updated: 2025/09/03 22:14:29 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	get_texture_color(int x, int y, t_sprite texture)
{
	char	*pixel;

	if (x < 0 || x >= texture.width || y < 0 || y >= texture.height)
	{
		return (ERROR_COLOR);
	}
	pixel = texture.mlx_data.bit_addr + (y
			* texture.mlx_data.line_len + x * texture.mlx_data.bpp / 8);
	return (*(int *)pixel);
}

int	get_north_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	int	wall_x;
	int	pixel_hit_x;
	int	wall_y;
	int	y_start;
	int	color;

	pixel_hit_x = ray.hit_x * WALL_SIZE;
	wall_x = pixel_hit_x % WALL_SIZE;
	wall_x = WALL_SIZE - wall_x - 1;
	wall_x = (wall_x * map->north_wall_texture->width) / WALL_SIZE;
	y_start = WIN_HEIGHT / 2 - y_len / 2;
	wall_y = ((pixel.y - y_start) * map->north_wall_texture->height) / y_len;
	color = get_texture_color(wall_x, wall_y, *map->north_wall_texture);
	return (color);
}

int	get_south_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	int	wall_x;
	int	pixel_hit_x;
	int	wall_y;
	int	y_start;
	int	color;

	pixel_hit_x = ray.hit_x * WALL_SIZE;
	wall_x = pixel_hit_x % WALL_SIZE;
	wall_x = (wall_x * map->south_wall_texture->width) / WALL_SIZE;
	y_start = WIN_HEIGHT / 2 - y_len / 2;
	wall_y = ((pixel.y - y_start) * map->south_wall_texture->height) / y_len;
	color = get_texture_color(wall_x, wall_y, *map->south_wall_texture);
	return (color);
}

int	get_west_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	int	wall_x;
	int	wall_y;
	int	pixel_hit_y;
	int	y_start;
	int	color;

	pixel_hit_y = ray.hit_y * WALL_SIZE;
	wall_x = pixel_hit_y % WALL_SIZE;
	wall_x = (wall_x * map->west_wall_texture->width) / WALL_SIZE;
	y_start = WIN_HEIGHT / 2 - y_len / 2;
	wall_y = ((pixel.y - y_start) * map->west_wall_texture->height) / y_len;
	color = get_texture_color(wall_x, wall_y, *map->west_wall_texture);
	return (color);
}

int	get_east_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	int	wall_x;
	int	wall_y;
	int	pixel_hit_y;
	int	y_start;
	int	color;

	pixel_hit_y = ray.hit_y * WALL_SIZE;
	wall_x = pixel_hit_y % WALL_SIZE;
	wall_x = WALL_SIZE - wall_x - 1;
	wall_x = (wall_x * map->east_wall_texture->width) / WALL_SIZE;
	y_start = WIN_HEIGHT / 2 - y_len / 2;
	wall_y = ((pixel.y - y_start) * map->east_wall_texture->height) / y_len;
	color = get_texture_color(wall_x, wall_y, *map->east_wall_texture);
	return (color);
}
