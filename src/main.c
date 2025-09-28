/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:09 by federico          #+#    #+#             */
/*   Updated: 2025/09/21 17:19:34 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	program_init(void *mlx,
		t_program *program, t_map *map, t_player *player)
{
	program->commands.w = false;
	program->commands.a = false;
	program->commands.s = false;
	program->commands.d = false;
	program->commands.l_arrow = false;
	program->commands.r_arrow = false;
	program->rendered = true;
	if (setup_mlx(mlx, &(program->mlx_data)) == FAILURE)
	{
		program->exit_status = MLX_ERR;
		return (FAILURE);
	}
	program->map = map;
	program->player_cnt = 0;
	if (player_init(player, *map, program) == FAILURE)
		return (FAILURE);
	program->player = player;
	return (SUCCESS);
}

void	rendering(t_program *program)
{
	hook_handlers(program);
	mlx_loop_hook(program->mlx_data.mlx, rend_loop, program);
	mlx_loop(program->mlx_data.mlx);
}

int	main(int argc, char **argv)
{
	void		*mlx;
	t_map		*map;
	t_player	player;
	t_program	program;

	mlx = mlx_init();
	if (mlx == NULL)
		exit(MLX_ERR);
	map = parsing(argc, argv[1], mlx);
	if (map == NULL)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return (1);
	}
	if (program_init(mlx, &program, map, &player) != SUCCESS)
		program_close(&program, program.exit_status);
	rendering(&program);
	return (2);
}
