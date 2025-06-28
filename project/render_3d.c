/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:22:10 by federico          #+#    #+#             */
/*   Updated: 2025/06/29 01:52:06 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	render_3d(t_program *program)
{
	printf("aim_len-> %f wall_side-> %d\n", program->player->aim.len, program->player->aim.wall_side);
	printf("hit_x-> %f hit_y->%f\n\n", program->player->aim.hit_x, program->player->aim.hit_y);
}
