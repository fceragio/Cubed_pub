/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:21:34 by federico          #+#    #+#             */
/*   Updated: 2025/06/27 14:25:51 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	not_wall(int x, int y, t_program *program)
{
	int	**arr;
	int	limit;

	limit = program->map->dimension;
	if (x < 0 || x >= limit || y < 0 || y >= limit)
		return (0);
	arr = program->map->arr;
	if (arr[y][x] == 1)
		return (0);
	return (1);
}
