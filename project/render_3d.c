/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:22:10 by federico          #+#    #+#             */
/*   Updated: 2025/06/28 16:37:31 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	render_3d(t_program *program)
{
	double	distance;
	int		wall_side;

	wall_side = find_wall_distance(&distance, program->player->aim, program->map, program);
	printf("distance-> %f, hit_type-> %d\n\n", distance, wall_side);
}
