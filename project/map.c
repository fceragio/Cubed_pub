/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:21:34 by federico          #+#    #+#             */
/*   Updated: 2025/06/23 22:25:36 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	not_wall(int x, int y, t_program *program)
{
	int	**arr;

	arr = program->map->arr;
	if (arr[y][x] == 1)
		return (0);
	return (1);
}
