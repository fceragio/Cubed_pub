/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:34:36 by kkurose           #+#    #+#             */
/*   Updated: 2025/09/12 18:40:13 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrap_angle(double *a)
{
	while (*a < 0)
		*a += 2 * M_PI;
	while (*a >= 2 * M_PI)
		*a -= 2 * M_PI;
}

double	safe_cos(double a)
{
	double	angle;

	angle = cos(a);
	if (fabs(angle) < EPSILON)
	{
		if (angle < 0)
			return (-EPSILON);
		return (EPSILON);
	}
	return (angle);
}

double	safe_sin(double a)
{
	double	angle;

	angle = sin(a);
	if (fabs(angle) < EPSILON)
	{
		if (angle < 0)
			return (-EPSILON);
		return (EPSILON);
	}
	return (angle);
}

double	safe_tan(double a)
{
	double	angle;

	angle = tan(a);
	if (fabs(angle) < EPSILON)
	{
		if (angle < 0)
			return (-EPSILON);
		return (EPSILON);
	}
	if (fabs(angle) > 1 / EPSILON)
	{
		if (angle < 0)
			return (-1 / EPSILON);
		return (1 / EPSILON);
	}
	return (angle);
}
