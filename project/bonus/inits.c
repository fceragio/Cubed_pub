/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:35:29 by federico          #+#    #+#             */
/*   Updated: 2025/07/02 15:57:27 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	vs_init(t_program *program)
{
	program->mlx_data.mlx = mlx_init();
	if (!program->mlx_data.mlx)
	{
		destroy_map(program->map);
		exit(MLX_ERR);
	}
	program->mlx_data.win = mlx_new_window(program->mlx_data.mlx, WIN_WIDTH, WIN_HEIGHT, "Cubed");
	if (!program->mlx_data.win)
	{
		destroy_map(program->map);
		mlx_destroy_display(program->mlx_data.mlx);
		free(program->mlx_data.mlx);
		exit(MLX_ERR);
	}
	program->mlx_data.img = mlx_new_image(program->mlx_data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!program->mlx_data.img)
	{
		destroy_map(program->map);
		mlx_destroy_window(program->mlx_data.mlx, program->mlx_data.win);
		mlx_destroy_display(program->mlx_data.mlx);
		free(program->mlx_data.mlx);
		exit(MLX_ERR);
	}
	program->mlx_data.bit_addr = mlx_get_data_addr(program->mlx_data.img, &program->mlx_data.bpp, &program->mlx_data.line_len, &program->mlx_data.endian);
	if (!program->mlx_data.bit_addr)
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

void	map_init(t_map *map, t_mlx_data *mlx_data)
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
	map->north_wall_texture = sprite_init(mlx_data->mlx, "../north.xpm");
	map->south_wall_texture = sprite_init(mlx_data->mlx, "../south.xpm");
	map->west_wall_texture = sprite_init(mlx_data->mlx, "../west.xpm");
	map->east_wall_texture = sprite_init(mlx_data->mlx, "../east.xpm");
}

t_sprite	*sprite_init(void *mlx, char *path)
{
	printf("initializing sprite\n");
	t_sprite	*result;

	result = malloc(sizeof(t_sprite));
	if (result == NULL)
		exit(1);
	//remember to manage later;
	printf("1\n");
	result->mlx_data.mlx = NULL;
	result->mlx_data.win = NULL;
	result->mlx_data.img = mlx_xpm_file_to_image(mlx, path, &result->width, &result->height);
	if (result->mlx_data.img == NULL)
		exit(2);
	printf("1\n");
	//manage later;
	result->mlx_data.bit_addr = mlx_get_data_addr(result->mlx_data.img, &result->mlx_data.bpp, &result->mlx_data.line_len, &result->mlx_data.endian);
	if (result->mlx_data.bit_addr == NULL)
		exit(3);
	printf("1\n");
	//manage later;
	printf("sprite initialized\n");
	return (result);
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
	mlx_destroy_image(program->mlx_data.mlx, program->mlx_data.img);
	mlx_destroy_window(program->mlx_data.mlx, program->mlx_data.win);
	mlx_destroy_display(program->mlx_data.mlx);
	free(program->mlx_data.mlx);
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
