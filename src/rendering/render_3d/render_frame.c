/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:41:57 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/17 02:13:32 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_3d(t_program *program)
{
	draw_floor_ceiling(program);
	draw_walls(program);
}
