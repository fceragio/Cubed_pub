/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:42:31 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/28 18:34:48 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_program *program, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	offset = (y * program->mlx_data.line_len) + (x * program->mlx_data.bpp / 8);
	*(unsigned int *)(program->mlx_data.bit_addr + offset) = color;
}

void	render(t_program *program)
{
	program->rendered = false;
	render_3d(program);
	mlx_put_image_to_window(program->mlx_data.mlx,
		program->mlx_data.win, program->mlx_data.img, MLX_DEFAULT, MLX_DEFAULT);
	program->rendered = true;
}

static void	set_next_door_frame(unsigned char animation, t_map *map)
{
	if (animation % (FPS / ANIMATION_RATE) == 0)
	{
		map->door_frame++;
		if (map->door_frame == DOOR_FILES)
			map->door_frame = 0;
	}
	map->door_texture = map->door_arr[map->door_frame];
}

int	rend_loop(t_program *program)
{
	struct timeval			time;
	long long int			tot_time;
	static long long int	last_time = 0;
	static unsigned char	animation = 0;

	if (gettimeofday(&time, NULL) == -1)
	{
		program_close(program, TIME_ERR);
	}
	tot_time = (time.tv_sec * MICROSECONDS_PERSEC + time.tv_usec);
	if (program->rendered == false
		|| (tot_time - last_time) < (MICROSECONDS_PERSEC / FPS))
		return (FAILURE);
	move_player(program);
	render(program);
	animation++;
	set_next_door_frame(animation, program->map);
	last_time = tot_time;
	return (SUCCESS);
}

void	program_close(t_program *program, int status)
{
	mlx_mouse_show(program->mlx_data.mlx, program->mlx_data.win);
	if (program->map)
		destroy_map(program->map);
	if (program->mlx_data.img)
		mlx_destroy_image(program->mlx_data.mlx, program->mlx_data.img);
	if (program->mlx_data.win)
		mlx_destroy_window(program->mlx_data.mlx, program->mlx_data.win);
	if (program->mlx_data.mlx)
	{
		mlx_destroy_display(program->mlx_data.mlx);
		free(program->mlx_data.mlx);
	}
	program->exit_status = status;
	exit(status);
}
