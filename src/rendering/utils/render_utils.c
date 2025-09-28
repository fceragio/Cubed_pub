/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:42:31 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/26 17:42:55 by federico         ###   ########.fr       */
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
	if (DEBUG_MODE)
		render_2d(program);
	else
		render_3d(program);
	mlx_put_image_to_window(program->mlx_data.mlx,
		program->mlx_data.win, program->mlx_data.img, MLX_DEFAULT, MLX_DEFAULT);
	program->rendered = true;
}

int	rend_loop(t_program *program)
{
	struct timeval			time;
	long long int			tot_time;
	static long long int	last_time = 0;

	if (gettimeofday(&time, NULL) == -1)
	{
		program_close(program, TIME_ERR);
	}
	tot_time = (time.tv_sec * MICROSECONDS_PERSEC + time.tv_usec);
	if (program->rendered == true
		&& (tot_time - last_time) >= (MICROSECONDS_PERSEC / FPS))
	{
		move_player(program);
		render(program);
		last_time = tot_time;
	}
	return (SUCCESS);
}

void	program_close(t_program *program, int status)
{
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
