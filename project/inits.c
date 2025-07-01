/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:35:29 by federico          #+#    #+#             */
/*   Updated: 2025/07/01 16:13:04 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	vs_init(t_program *program)
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

void	commands_init(t_program *program)
{
	program->commands.w = false;
	program->commands.a = false;
	program->commands.s = false;
	program->commands.d = false;
	program->commands.l_arrow = false;
	program->commands.r_arrow = false;
}

void	map_init(t_map *map)
{
	map->floor_color = FLOOR;
	map->sealing_color = SEALING;
	map->dimension = 16;
	map->arr = malloc(sizeof(int *) * map->dimension);

	int	i;
	int	j;
	int	temp[16][16] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
						{1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
						{1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
						{1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
						{1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
						{1, 0, 1, 1, 0, 0, 0, EAST, 0, 0, 0, 1, 1, 1, 1, 1},
						{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1},
						{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1},
						{1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
						{1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
						{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
						{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},};
	i = 0;
	while (i < map->dimension)
	{
		map->arr[i] = malloc(sizeof(int) * map->dimension);
		i++;
	}
	i = 0;
	while (i < map->dimension)
	{
		j = 0;
		while (j < map->dimension)
		{
			map->arr[i][j] = temp[i][j];
			j++;
		}
		i++;
	}
}

void	player_init(t_player *player, t_map map, t_program *program)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.dimension)
	{
		x = 0;
		while (x < map.dimension)
		{
			if (map.arr[y][x] != 0 && map.arr[y][x] != 1)
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				player->angle = map.arr[y][x];
			}
			x++;
		}
		y++;
	}
	if (player->angle == NORTH)
		player->angle = 3 * M_PI / 2;
	if (player->angle == SOUTH)
		player->angle = M_PI / 2;
	if (player->angle == EAST)
		player->angle = 0;
	if (player->angle == WEST)
		player->angle = M_PI;
	player_aim_init(player, program);
}

void	player_aim_init(t_player *player, t_program *program)
{
	int		i;
	double	angle;
	double	angle_step;

	ray_init(&player->aim, player, player->angle, program);
	angle = player->angle - (FOV / 2.0);
	angle_step = FOV / ((double)NUM_RAYS - 1);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_init(&player->fov[i], player, angle, program);
		angle += angle_step;
		i++;
	}
}

void	ray_init(t_ray *ray, t_player *player, double angle, t_program *program)
{
	safe_angle(&angle);
	ray->x = player->x;
	ray->y = player->y;
	ray->angle = angle;
	ray->dir_x = safe_cos(angle);
	ray->dir_y = safe_sin(angle);
	if (ray->dir_x > 0)
		ray->step_x = +1;
	else
		ray->step_x = -1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = +1;
	ray->wall_side = find_wall_distance(&ray->len, ray, program->map, program);
	ray->distance = ray->len * safe_cos(ray->angle - player->angle);
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
	while (i < map->dimension)
	{
		free(map->arr[i]);
		i++;
	}
	free(map->arr);
}
