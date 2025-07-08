/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:00:52 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 02:27:49 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

double	safe_cos(double angle)
{
	double	tmp;

	tmp = cos(angle);
	if (fabs(tmp) < EPSILON)
	{
		if (tmp < 0)
			return (-EPSILON);
		return (EPSILON);
	}
	return (tmp);
}

double	safe_sin(double angle)
{
	double	tmp;

	tmp = sin(angle);
	if (fabs(tmp) < EPSILON)
	{
		if (tmp < 0)
			return (-EPSILON);
		return (EPSILON);
	}
	return (tmp);
}

double	safe_tan(double angle)
{
	double	tmp;

	tmp = tan(angle);
	if (fabs(tmp) < EPSILON)
	{
		if (tmp < 0)
			return (-EPSILON);
		return (EPSILON);
	}
	if (fabs(tmp) > (1 / EPSILON))
	{
		if (tmp < 0)
			return (-1 / EPSILON);
		return (1 / EPSILON);
	}
	return (tmp);
}

void	safe_angle(double *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle = *angle + (2 * M_PI);
}
