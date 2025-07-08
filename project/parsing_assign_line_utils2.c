/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assign_line_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:58:59 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 01:33:42 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	assign_line_c(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->C_flag == true)
	{
		print_error("Error\nMore lines contain cealing color\n");
		free(line);
		return (FAILURE);
	}
	blueprint->C_flag = true;
	blueprint->C = line;
	return (SUCCESS);
}

int	assign_line_f(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->F_flag == true)
	{
		print_error("Error\nMore lines contain floor color\n");
		free(line);
		return (FAILURE);
	}
	blueprint->F_flag = true;
	blueprint->F = line;
	return (SUCCESS);
}
