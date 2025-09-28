/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:33:01 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/21 17:36:34 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	setup_mlx(void *mlx, t_mlx_data *mlx_data)
{
	mlx_data->mlx = mlx;
	mlx_data->win = mlx_new_window(mlx_data->mlx,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!mlx_data->win)
		return (print_err(ERR_HEAD), print_err(NEW_WIN_ERR), FAILURE);
	mlx_data->img = mlx_new_image(mlx_data->mlx,
			WIN_WIDTH, WIN_HEIGHT);
	if (!mlx_data->img)
		return (print_err(ERR_HEAD), print_err(NEW_IMG_ERR), FAILURE);
	mlx_data->bit_addr = mlx_get_data_addr(mlx_data->img,
			&mlx_data->bpp, &mlx_data->line_len, &mlx_data->endian);
	if (!mlx_data->bit_addr)
		return (print_err(ERR_HEAD), print_err(DATA_ADDR_ERR), FAILURE);
	return (SUCCESS);
}
