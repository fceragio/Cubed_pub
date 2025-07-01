/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:22:10 by federico          #+#    #+#             */
/*   Updated: 2025/07/01 20:49:40 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	render_sealing(t_program *program)
{
	int	x;
	int	y;

	x = 0;
	while (x <= WIN_WIDTH)
	{
		y = 0;
		while (y < (WIN_HEIGHT / 2))
		{
			put_pixel(program, x, y, program->map->sealing_color);
			y++;
		}
		x++;
	}
}

static void	render_floor(t_program *program)
{
	int	x;
	int	y;

	x = 0;
	while (x <= WIN_WIDTH)
	{
		y = (WIN_HEIGHT / 2);
		while (y < WIN_HEIGHT)
		{
			put_pixel(program, x, y, program->map->floor_color);
			y++;
		}
		x++;
	}
}

static int	get_texture_color(int x, int y, t_sprite texture)
{
	char	*pixel;

	if (x < 0 || x >= texture.width || y < 0 || y >= texture.height)
		return (ERROR_COLOR);
	pixel = texture.mlx_data.bit_addr + (y * texture.mlx_data.line_len + x * texture.mlx_data.bpp / 8);
	return (*(int *)pixel);
}

int	get_north_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	int	wall_x;
	int	wall_y;
	int	y_start;
	int	color;

	wall_x = (int)ray.hit_x % TILE_SIZE;
	wall_x = (wall_x * map->north_wall_texture->width) / TILE_SIZE;
	y_start = WIN_HEIGHT / 2 - y_len / 2;
	wall_y = ((pixel.y - y_start) * map->north_wall_texture->height) / y_len;
	color = get_texture_color(wall_x, wall_y, *map->north_wall_texture);
	return (color);
}
int	get_south_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	int	wall_x;
	int	wall_y;
	int	y_start;
	int	color;

	wall_x = (int)ray.hit_x % TILE_SIZE;
	wall_x = (wall_x * map->south_wall_texture->width) / TILE_SIZE;
	y_start = WIN_HEIGHT / 2 - y_len / 2;
	wall_y = ((pixel.y - y_start) * map->south_wall_texture->height) / y_len;
	color = get_texture_color(wall_x, wall_y, *map->south_wall_texture);
	return (color);
}
int	get_west_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	int	wall_x;
	int	wall_y;
	int	y_start;
	int	color;

	wall_x = (int)ray.hit_y % TILE_SIZE;
	wall_x = (wall_x * map->west_wall_texture->width) / TILE_SIZE;
	y_start = WIN_HEIGHT / 2 - y_len / 2;
	wall_y = ((pixel.y - y_start) * map->west_wall_texture->height) / y_len;
	color = get_texture_color(wall_x, wall_y, *map->west_wall_texture);
	return (color);
}
int	get_east_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	int	wall_x;
	int	wall_y;
	int	y_start;
	int color;

	wall_x = (int)ray.hit_y % TILE_SIZE;
	wall_x = (wall_x * map->east_wall_texture->width) / TILE_SIZE;
	y_start = WIN_HEIGHT / 2 - y_len / 2;
	wall_y = ((pixel.y - y_start) * map->east_wall_texture->height) / y_len;
	color = get_texture_color(wall_x, wall_y, *map->east_wall_texture);
	return (color);
}

static int	get_wall_color(t_map *map, t_ray ray, t_point pixel, int y_len)
{
	if (ray.wall_side == NORTH)
		return (get_north_wall_color(map, ray, pixel, y_len));
	else if (ray.wall_side == SOUTH)
		return (get_south_wall_color(map, ray, pixel, y_len));
	else if (ray.wall_side == WEST)
		return (get_west_wall_color(map, ray, pixel, y_len));
	else if (ray.wall_side == EAST)
		return (get_east_wall_color(map, ray, pixel, y_len));
	return (FAILURE);
}

static void	put_ray_pixels(t_point pixel, t_program *program)
{
	int	y;
	int	y_start;
	int	y_end;
	int	color;
	int	i;

	i = pixel.y;
	y_start = (WIN_HEIGHT / 2) - (WALL_SIZE / program->player->fov[i].distance) / 2;
	y_end = (WIN_HEIGHT / 2) + (WALL_SIZE / program->player->fov[i].distance) / 2;
	y = y_start;
	while (y <= y_end)
	{
		pixel.y = y;
		color = get_wall_color(program->map, program->player->fov[i], pixel, y_end - y_start);
		put_pixel(program, pixel.x, pixel.y, color);
		y++;
	}
}

static void	render_walls(t_program *program)
{
	t_point	pixel;
			int	i;
			int	x;

	i = 0;
	while (i <= NUM_RAYS)
	{
		x = WID_RAYS * i;
		while (x <= (WID_RAYS * (i + 1)))
		{
			pixel.x = x;
			pixel.y = i;
			put_ray_pixels(pixel, program);
			x++;
		}
		i++;
	}
}

void	render_3d(t_program *program)
{
	render_sealing(program);
	render_floor(program);
	render_walls(program);
}
