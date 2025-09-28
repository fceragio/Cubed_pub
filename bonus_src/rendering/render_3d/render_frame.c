/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:41:57 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/27 10:50:45 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_3d(t_program *program)
{
	draw_floor_ceiling(program);
	draw_walls(program);
	if (program->rend_map == true)
		render_2d(program);
}
