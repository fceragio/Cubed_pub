/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:07:09 by federico          #+#    #+#             */
/*   Updated: 2025/09/02 01:02:08 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
	program_init(mlx, &program, map, &player);
	rendering(&program);
	return (2);
}

void	program_init(void *mlx,
		t_program *program, t_map *map, t_player *player)
{
	program->commands.w = NO;
	program->commands.a = NO;
	program->commands.s = NO;
	program->commands.d = NO;
	program->commands.l_arrow = NO;
	program->commands.r_arrow = NO;
	program->rendered = YES;
	vs_init(mlx, program);
	program->map = map;
	player_init(player, *map, program);
	program->player = player;
}

void	rendering(t_program *program)
{
	hook_handlers(program);
	mlx_loop_hook(program->mlx_data.mlx, rend_loop, program);
	mlx_loop(program->mlx_data.mlx);
}
