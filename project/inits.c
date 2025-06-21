/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:35:29 by federico          #+#    #+#             */
/*   Updated: 2025/06/22 02:54:59 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	program_init(t_program *program)
{
	program->mlx = mlx_init();
	if (!program->mlx)
	{
		destroy_map(program->map);
		exit(MLX_ERR);
	}
	program->win = mlx_new_window(program->mlx, WIN_WIDTH, WIN_HEIGHT, "Cubed");
	if (!program->win)
	{
		destroy_map(program->map);
		mlx_destroy_display(program->mlx);
		free(program->mlx);
		exit(MLX_ERR);
	}
	program->img = mlx_new_image(program->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!program->img)
	{
		destroy_map(program->map);
		mlx_destroy_window(program->mlx, program->win);
		mlx_destroy_display(program->mlx);
		free(program->mlx);
		exit(MLX_ERR);
	}
	program->bit_addr = mlx_get_data_addr(program->img, &program->bpp, &program->line_len, &program->endian);
	if (!program->bit_addr)
		program_close(program, MLX_ERR);
}

void	map_init(t_map *map)
{
	map->width = 8;
	map->height = 8;
	map->arr = malloc(sizeof(int *) * map->height);

	int	i;
	int	j;
	int	temp[8][8] = {{1, 1, 1, 1, 1, 1, 1, 1},
					{1, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 1, 0, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 0, 0, 1, 1, 0, 1},
					{1, 0, 0, 0, 9, 1, 0, 1},
					{1, 0, 0, 0, 0, 1, 0, 1},
					{1, 1, 1, 1, 1, 1, 1, 1}};
	i = 0;
	while (i < map->height)
	{
		map->arr[i] = malloc(sizeof(int) * map->width);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->arr[i][j] = temp[i][j];
			j++;
		}
		i++;
	}
}

void	player_init(t_player *player, t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.arr[y][x] != 0 && map.arr[y][x] != 1)
			{
				player->x = x * TILE_SIZE - TILE_SIZE / 2;
				player->y = y * TILE_SIZE - TILE_SIZE / 2;
				player->angle = map.arr[y][x];
			}
			x++;
		}
		y++;
	}
	if (player->angle == NORTH)
		player->angle = M_PI / 2;
	if (player->angle == SOUTH)
		player->angle = -M_PI / 2;
	if (player->angle == EAST)
		player->angle = M_PI;
	if (player->angle == WEST)
		player->angle = -M_PI;
	printf("player angle = %f\n", player->angle);
}

int	program_close(t_program *program, int status)
{
	mlx_destroy_image(program->mlx, program->img);
	mlx_destroy_window(program->mlx, program->win);
	mlx_destroy_display(program->mlx);
	free(program->mlx);
	destroy_map(program->map);
	exit(status);
	return (status);
}

void	destroy_map(t_map *map)
{
	int	i;

	if (!map || !map->arr)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->arr[i]);
		i++;
	}
	free(map->arr);
}
