/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_program_init_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:29:13 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 01:29:26 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	vs_init(void *mlx, t_program *program)
{
	program->mlx_data.mlx = mlx;
	program->mlx_data.win = mlx_new_window(program->mlx_data.mlx,
			WIN_WIDTH, WIN_HEIGHT, "Cubed");
	if (!program->mlx_data.win)
	{
		destroy_map(program->map);
		mlx_destroy_display(program->mlx_data.mlx);
		free(program->mlx_data.mlx);
		exit(MLX_ERR);
	}
	program->mlx_data.img = mlx_new_image(program->mlx_data.mlx,
			WIN_WIDTH, WIN_HEIGHT);
	if (!program->mlx_data.img)
	{
		destroy_map(program->map);
		mlx_destroy_window(program->mlx_data.mlx, program->mlx_data.win);
		mlx_destroy_display(program->mlx_data.mlx);
		free(program->mlx_data.mlx);
		exit(MLX_ERR);
	}
	program->mlx_data.bit_addr = mlx_get_data_addr(program->mlx_data.img,
			&program->mlx_data.bpp, &program->mlx_data.line_len,
			&program->mlx_data.endian);
	if (!program->mlx_data.bit_addr)
		program_close(program, MLX_ERR);
}

int	program_close(t_program *program, int status)
{
	destroy_map(program->map);
	mlx_destroy_image(program->mlx_data.mlx, program->mlx_data.img);
	mlx_destroy_window(program->mlx_data.mlx, program->mlx_data.win);
	mlx_destroy_display(program->mlx_data.mlx);
	free(program->mlx_data.mlx);
	exit(status);
	return (status);
}
